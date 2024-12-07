

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
    body = new Cube();
    leftLeg = new Cube();
    rightLeg = new Cube();
    leftArm = new Cube();
    rightArm = new Cube();
    head = new Cube();

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
}

void Robot::update(float deltaTime) {
    // 로봇의 상태 업데이트
    updatePartTransforms();
    
    
}

void Robot::updatePartTransforms() {

    // 몸통 변환
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f, 0.f));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.5f, 0.5f));

    // 왼쪽 다리 변환
    leftLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.25f, -0.5f, 0.f));
    leftLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));

    // 오른쪽 다리 변환
    rightLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.25f, -0.f, 0.f));
    rightLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));

    // 왼쪽 팔 변환
    leftArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.75f, 1.f, 0.f));
    leftArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));

    // 오른쪽 팔 변환
    rightArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.75f, 1.f, 0.f));
    rightArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));

    // 머리 변환
    head->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 2.5f, 0.f));
    head->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.75f, 0.75f, 0.75f));

}

void Robot::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        part->_FT = part->_trs * part->_scale;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);
    }
}

