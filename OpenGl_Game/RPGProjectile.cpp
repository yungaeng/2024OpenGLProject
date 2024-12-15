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
        // 범위를 벗어나면 파괴
        SetDead();
        DeleteObject(this);
        return;
    }

    // 이동
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
			// glu 삭제
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
    // 폭발 처리
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Monster* mon = dynamic_cast<Monster*>(otherObject)) {
       
		_glu_exp = new GLU_Object();
		_glu_exp->setTranslation(_parts[0]->_trs);
		_glu_exp->setScale(vec3(1,0.75,1));
		_glu_exp->setFT();
    }
    // 폭발 중심 위치를 계산합니다.
    vec3 explosionCenter = vec3(_parts[0]->_trs[3]);
    // 씬 매니저에서 모든 몬스터들을 가져옵니다.
    auto& monsters = SceneManager::getInstance().GetGroupObject(GROUP_TYPE::MONSTER);
    // 모든 몬스터들을 순회하며 폭발 반경 내에 있는지 확인하고 피해를 줍니다.
    for (auto& obj : monsters) {
        Monster* monster = dynamic_cast<Monster*>(obj);
        if (monster && monster->IsDead() == false) {
            // 몬스터의 위치를 가져옵니다.
            vec3 monsterPos = monster->getObjectPos();

            // 폭발 중심과 몬스터 사이의 거리를 계산합니다.
            float distance = glm::distance(explosionCenter, monsterPos);

            // 거리가 폭발 반경 이내라면 피해를 줍니다.
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
