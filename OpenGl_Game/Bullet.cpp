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
    // 총알이 총구에서 나오도록 위치 조정
	_objectpos += _direction * 0.5f;

    // _body 초기화
    _body->_owner = this;
    _body->_trs = glm::translate(glm::mat4(1.0f), _objectpos);
    _body->_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // 총알 크기 설정
	_body->_FT = _body->_trs * _body->_rot * _body->_scale;
    _body->setColor(vec3(1.0f, 0.0f, 0.0f)); // 총알 색상 설정
    

    // Collider 초기화
    _body->initCollider(); 
    addPart(_body);
}

Bullet::~Bullet() 
{
    // 필요한 경우 리소스 해제
    delete _body;
}

void Bullet::update(float deltaTime) {
    // 총알 위치 업데이트
    vec3 movement = _direction * _speed * deltaTime;
    _objectpos += movement;
    _traveledDistance += glm::length(movement);

    // _body의 변환 행렬 업데이트
    _body->_trs = glm::translate(glm::mat4(1.0f), _objectpos);
    _body->_FT = _body->_trs * _body->_rot * _body->_scale;

    // Collider 위치 업데이트
	if (_body->_collider != nullptr)
        _body->updateCollider();
    
    // 범위를 벗어나면 객체 제거
    if (isOutOfRange()) {
		DeleteObject(this);
    }
}

void Bullet::draw(GLuint shaderProgramID) {
    // 총알 그리기
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
    // 충돌한 객체의 소유자를 가져옵니다.
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Robot* robot = dynamic_cast<Robot*>(otherObject)) {
        // 로봇에 데미지를 입힙니다.
        //robot->TakeDamage(_damage);
        // Bullet은 소멸합니다.
        DeleteObject(this);
    }
}
