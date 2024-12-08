

// Robot.cpp
#include "Robot.h"

Robot::Robot() {
    initializeParts();
}

Robot::~Robot() {
    delete body;
    delete leftLeg;
    delete rightLeg;
    delete leftArm;
    delete rightArm;
    delete head;
}

void Robot::initializeParts() {
    body = new Cube("body");
    leftLeg = new Cube("leftleg");
    rightLeg = new Cube("rightleg");
    leftArm = new Cube("leftarm");
    rightArm = new Cube("rightarm");
    head = new Cube("head");

    // Collider 초기화
    body->initCollider();
    leftLeg->initCollider();
    rightLeg->initCollider();
    leftArm->initCollider();
    rightArm->initCollider();
    head->initCollider();

    addPart(body);
    addPart(leftLeg);
    addPart(rightLeg);
    addPart(leftArm);
    addPart(rightArm);
    addPart(head);

	for (auto& a : _parts)
	{
		a->initCollider();
		a->_owner = this;
	}
}

void Robot::update(float deltaTime) {
    // 로봇의 상태 업데이트
    updatePartTransforms();
	Object::update(deltaTime);
    
}

void Robot::updatePartTransforms() {

    // 몸통 변환
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f, 0.f));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.5f, 0.5f));
	body->_FT = body->_trs * body->_scale;
    // 왼쪽 다리 변환
    leftLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.25f, -0.5f, 0.f));
    leftLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
	leftLeg->_FT = leftLeg->_trs * leftLeg->_scale;
    // 오른쪽 다리 변환
    rightLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.25f, -0.f, 0.f));
    rightLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
	rightLeg->_FT = rightLeg->_trs * rightLeg->_scale;
    // 왼쪽 팔 변환
    leftArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.75f, 1.f, 0.f));
    leftArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
	leftArm->_FT = leftArm->_trs * leftArm->_scale;
    // 오른쪽 팔 변환
    rightArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.75f, 1.f, 0.f));
    rightArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
	rightArm->_FT = rightArm->_trs * rightArm->_scale;
    // 머리 변환
    head->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 2.5f, 0.f));
    head->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.75f, 0.75f, 0.75f));
	head->_FT = head->_trs * head->_scale;
}

void Robot::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);
    }
}

