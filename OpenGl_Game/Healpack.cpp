// Healpack.cpp

#include "Healpack.h"
#include "Collider.h"
#include "Player.h"
#include "Gun.h"
#include "func.h"
#include "SceneManager.h"
Healpack::Healpack()
{
    setObjectPos(glm::vec3(0.f, 0.3f, -10.f));
    initializeParts();
	random_xpos = Random_0_to_1f() * 5.5f - 3;
	zpos = -10.f;
}

Healpack::~Healpack() {
    delete body;
    delete cross;
	Object::~Object();
}

void Healpack::initializeParts() {
    body = new Cube("body");
    cross = new Cube("cross");
	// color select
	body->setColor(glm::vec3(0.1f, 1.0f, 0.1f));
	cross->setColor(glm::vec3(0.1f, 1.0f, 0.1f));


    // Collider 초기화
    body->initCollider();
    cross->initCollider();

    addPart(body);
    addPart(cross);

    for (auto& a : _parts)
    {
        a->initCollider();
        a->_owner = this;
    }
}

// Healpack 클래스에 회전 상태를 저장할 멤버 변수 추가
float rotationAngle = 0.0f;

void Healpack::update(float deltaTime) {
    // 힐팩의 상태 업데이트
    updatePartTransforms();
    Object::update(deltaTime);

    // 회전 속도 설정 (초당 70도 회전)
    const float rotationSpeed = 70.f;

    // 누적 회전각 계산
    rotationAngle += rotationSpeed * deltaTime;
    if (rotationAngle > 360.f) rotationAngle -= 360.f; // 360도를 넘으면 초기화

    // 전진 속도 설정 (초당 1 단위 전진)
    const float moveSpeed = 1.0f;

	vec3 position = getObjectPos();

    // 전진 계산 (힐팩의 Z축 방향으로 이동)
	zpos += moveSpeed * deltaTime;
	

    // 힐팩 회전 및 이동 변환 적용
    body->_trs = glm::translate(glm::mat4(1.f), vec3(random_xpos,0.5,zpos));
    body->_FT = body->_trs * body->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.f)) * body->_scale;

    cross->_trs = glm::translate(glm::mat4(1.f), vec3(random_xpos,0.5f,zpos));
    cross->_FT = cross->_trs * cross->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * cross->_scale;

    // Collider 위치 업데이트
    if (body->_collider != nullptr)
        body->updateCollider();
    if (cross->_collider != nullptr)
        cross->updateCollider();

    // 범위를 벗어나면 객체 제거
    if (isOutOfRange()) {
        DeleteObject(this);
    }
}

void Healpack::updatePartTransforms() {
    // 몸통 변환
    body->_trs = glm::translate(glm::mat4(1.f), getObjectPos());
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.3f, 0.5f, 0.3f));
    body->_FT = body->_trs * body->_scale;

    // 중간 몸통 변환
    cross->_trs = glm::translate(glm::mat4(1.f), getObjectPos());
    cross->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.7f, 0.2f, 0.3f));
    cross->_FT = cross->_trs * cross->_scale;
}

extern bool render_aabb;
void Healpack::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

		if (part->_collider != nullptr && m_bAlive && render_aabb)
		{
			part->_collider->renderAABB(shaderProgramID);
		}
    }
}

void Healpack::OnCollisionEnter(Collider* _pOther)
{
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Gun* pgun = dynamic_cast<Gun*>(otherObject))
    {
        this->SetDead();
        DeleteObject(this);
		Player* p = SceneManager::getInstance().getPlayer();
        p->SetHp(p->GetHP() + 1);

    }
}

void Healpack::OnCollision(Collider* _pOther)
{
}

void Healpack::OnCollisionExit(Collider* _pOther)
{
	int a = 0;
}

bool Healpack::isOutOfRange() const
{
    return _traveledDistance >= _range;
}

