// RPGProjectile.cpp
#include "RPGProjectile.h"
#include "SceneManager.h"
#include "Collider.h"
#include "GLU_Object.h"
#include "Monster.h"
//#include "Model.h"

RPGProjectile::RPGProjectile(vec3 position, vec3 direction, float speed, float damage)
    : _direction(direction)
    , _speed(speed)
    , _damage(damage)
    , _range(200.f)
    , _traveledDistance(0.f)
    , _explosionRadius(7.f)
	, _glu_exp(nullptr)
	, _exduration(0.f)
{
    _body = new Cube("RocketBody");
    _body->_owner = this;
    _body->initCollider();
    _body->_trs = glm::translate(mat4(1.f), position);
    _body->_rot = glm::inverse(glm::lookAt(vec3(0.f), _direction, vec3(0.f, 1.f, 0.f)));
    _body->_scale = glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 0.5f));
    _body->_FT = _body->_trs * _body->_rot * _body->_scale;
    _parts.push_back(_body);
}

RPGProjectile::~RPGProjectile() {
    delete _body;
}

void RPGProjectile::update(float deltaTime) {
    float distance = _speed * deltaTime;
    _traveledDistance += distance;

    if (_traveledDistance >= _range) {
        // ������ ����� �ı�
        SetDead();
        DeleteObject(this);
        return;
    }

    // �̵�
    vec3 movement = _direction * distance;
    for (auto& part : _parts) {
        part->_trs = glm::translate(part->_trs, movement);
        part->_FT = part->_trs * part->_rot * part->_scale;

        if (part->_collider != nullptr) {
            part->updateCollider();
        }
    }
    if (_glu_exp != nullptr)
    {
        _exduration += deltaTime;
        if (_exduration > 0.5f)
        {
			// glu ����
			delete _glu_exp;
			_glu_exp = nullptr;
			SetDead();
			DeleteObject(this);
        }
    }
}

void RPGProjectile::draw(GLuint shaderProgramID) {

    if (_glu_exp != nullptr)
    {
        _glu_exp->draw(shaderProgramID);
    }
    else
    {
        for (auto& part : _parts) {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
            part->Draw(shaderProgramID);
        }
    }
}

void RPGProjectile::OnCollisionEnter(Collider* _pOther) {
    // ���� ó��
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Monster* mon = dynamic_cast<Monster*>(otherObject)) {
       
		_glu_exp = new GLU_Object();
		_glu_exp->setTranslation(_parts[0]->_trs);
		_glu_exp->setScale(vec3(1,0.75,1));
		_glu_exp->setFT();
    }
    // ���� �߽� ��ġ�� ����մϴ�.
    vec3 explosionCenter = vec3(_parts[0]->_trs[3]);
    // �� �Ŵ������� ��� ���͵��� �����ɴϴ�.
    auto& monsters = SceneManager::getInstance().GetGroupObject(GROUP_TYPE::MONSTER);
    // ��� ���͵��� ��ȸ�ϸ� ���� �ݰ� ���� �ִ��� Ȯ���ϰ� ���ظ� �ݴϴ�.
    for (auto& obj : monsters) {
        Monster* monster = dynamic_cast<Monster*>(obj);
        if (monster && monster->IsDead() == false) {
            // ������ ��ġ�� �����ɴϴ�.
            vec3 monsterPos = monster->getObjectPos();

            // ���� �߽ɰ� ���� ������ �Ÿ��� ����մϴ�.
            float distance = glm::distance(explosionCenter, monsterPos);

            // �Ÿ��� ���� �ݰ� �̳���� ���ظ� �ݴϴ�.
            if (distance <= _explosionRadius) {
                monster->SetHp(monster->getHp() - static_cast<int>(_damage));
                if (monster->getHp() <= 0) {
                    monster->SetDead();
                    DeleteObject(monster);
                }
            }
        }
    }
}

float RPGProjectile::getDamage() const {
    return _damage;
}

void RPGProjectile::setDamage(float damage) {
    _damage = damage;
}
