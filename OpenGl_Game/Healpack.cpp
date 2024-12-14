

// Healpack.cpp
#include "Healpack.h"
#include "Collider.h"

Healpack::Healpack() {
    initializeParts();
}

Healpack::~Healpack() {
    delete body;
    delete cross;
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

    // 힐팩 회전
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    body->_FT = body->_trs * body->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * body->_scale;

    cross->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    cross->_FT = cross->_trs * cross->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * cross->_scale;
}

void Healpack::updatePartTransforms() {
    // 몸통 변환
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.3f, 0.5f, 0.3f));
    body->_FT = body->_trs * body->_scale;
   // 중간 몸통 변환
    cross->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    cross->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.7f, 0.2f, 0.3f));
    cross->_FT = cross->_trs * cross->_scale;
}

void Healpack::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

		if (part->_collider != nullptr)
		{
			part->_collider->renderAABB(shaderProgramID);
		}
    }
}

