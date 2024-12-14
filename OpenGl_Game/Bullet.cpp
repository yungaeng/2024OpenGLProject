// Bullet.cpp
#include "Bullet.h"
#include <glm/gtc/matrix_transform.hpp>
#include "global.h"
#include "Collider.h"
#include "Robot.h"
#include "Eventmanager.h"


Bullet::Bullet(vec3 position, vec3 direction, float speed, float damage)
    :
    _direction(glm::normalize(direction))
    , _speed(speed)
    , _damage(damage)
    , _range(100.0f)
    , _traveledDistance(0.0f)
    , _body(new Cube ("Bullet"))
{
    _objectpos = position;
    // �Ѿ��� �ѱ����� �������� ��ġ ����
	_objectpos += _direction * 0.5f;

    // _body �ʱ�ȭ
    _body->_owner = this;
    _body->_trs = glm::translate(glm::mat4(1.0f), _objectpos);
    _body->_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // �Ѿ� ũ�� ����
	_body->_FT = _body->_trs * _body->_rot * _body->_scale;
    _body->setColor(vec3(1.0f, 0.0f, 0.0f)); // �Ѿ� ���� ����
    

    // Collider �ʱ�ȭ
    _body->initCollider(); 
    addPart(_body);
}

Bullet::~Bullet() 
{
    // �ʿ��� ��� ���ҽ� ����
    delete _body;
}

void Bullet::update(float deltaTime) {
    // �Ѿ� ��ġ ������Ʈ
    vec3 movement = _direction * _speed * deltaTime;
    _objectpos += movement;
    _traveledDistance += glm::length(movement);

    // _body�� ��ȯ ��� ������Ʈ
    _body->_trs = glm::translate(glm::mat4(1.0f), _objectpos);
    _body->_FT = _body->_trs * _body->_rot * _body->_scale;

    // Collider ��ġ ������Ʈ
	if (_body->_collider != nullptr)
        _body->updateCollider();
    
    // ������ ����� ��ü ����
    if (isOutOfRange()) {
		DeleteObject(this);
    }
}

void Bullet::draw(GLuint shaderProgramID) {
    // �Ѿ� �׸���
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(_body->_FT));
    _body->Draw(shaderProgramID);

    if (_body->_collider != nullptr && m_bAlive)
    {
        _body->_collider->renderAABB(shaderProgramID);
    }
}

bool Bullet::isOutOfRange() const {
    return _traveledDistance >= _range;
}

void Bullet::OnCollisionEnter(Collider* _pOther)
{
    // �浹�� ��ü�� �����ڸ� �����ɴϴ�.
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Robot* robot = dynamic_cast<Robot*>(otherObject)) {
        // �κ��� �������� �����ϴ�.
        //robot->TakeDamage(_damage);
        // Bullet�� �Ҹ��մϴ�.
        DeleteObject(this);
    }
}
