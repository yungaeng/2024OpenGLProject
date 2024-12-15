

// Robot.cpp
#include "global.h"
#include "Robot.h"
#include "Collider.h"
#include "Bullet.h"
#include "func.h"
#include "SceneManager.h"
#include "Player.h"

Robot::Robot() {
    initializeParts();
    _angle = 0.f;
	_theta = 90.f;
	_pos = -10.f;
	_random_xpos = Random_0_to_1f() * 5.5f - 3;
}

Robot::~Robot() {
    delete body;
    delete leftLeg;
    delete rightLeg;
    delete leftArm;
    delete rightArm;
    delete head;

	Object::~Object();
}

void Robot::initializeParts() {
    body = new Cube("body");
    leftLeg = new Cube("leftleg");
    rightLeg = new Cube("rightleg");
    leftArm = new Cube("leftarm");
    rightArm = new Cube("rightarm");
    head = new Cube("head");
    // color select
    
	body->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
	leftArm->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
	rightArm->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
	leftLeg->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
	rightLeg->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
	head->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
    _hp = 300;

    addPart(body);
    addPart(leftArm);
    addPart(rightArm);
    addPart(leftLeg);
    addPart(rightLeg);
   
    addPart(head);

	for (auto& a : _parts)
	{
		a->initCollider();
		a->_owner = this;
	}
}

void Robot::update(float deltaTime) {
    // 로봇의 상태 업데이트
   
    if (_angle >= 45.f)
        _theta = -90.f;
	else if (_angle <= -45.f)
		_theta = +90.f;
	_angle += _theta * deltaTime;

    
    if (_pos > 5)
    {
        SetDead();
        DeleteObject(this);
		SceneManager::getInstance().getPlayer()->SetHp(SceneManager::getInstance().getPlayer()->GetHP() - 1);
    }

    updatePartTransforms(deltaTime);
	Object::update(deltaTime);
    
}

void Robot::updatePartTransforms(float deltaTime) {
    // 로봇의 각 파츠의 위치, 회전, 스케일을 업데이트합니다.

    float width = 1.f;
    float height = 1.f;
    mat4 model = mat4(1.f);

    // 크기 
    float x_body_scale = 0.75;
    float y_body_scale = 0.6;
    float z_body_scale = 0.75;

    float x_leg_scale = 0.25;
    float y_leg_scale = 0.5;
    float z_leg_scale = 0.25;

    float x_arm_scale = 0.25;
    float y_arm_scale = 0.6;
    float z_arm_scale = 0.25;

    float x_head_scale = 0.5;
    float y_head_scale = 0.4;
    float z_head_scale = 0.5;


    _pos+= deltaTime;
    // 몸통 변환
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, height * y_leg_scale + height / 2 * y_body_scale, _pos));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_body_scale, y_body_scale, z_body_scale));
    body->_FT = body->_trs * body->_scale;

    // 왼쪽 다리 변환
    leftLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-x_body_scale * width / 2 + width / 2 * x_leg_scale, -height / 2 * y_leg_scale, 0));
    leftLeg->_rot = glm::rotate(mat4(1.f), glm::radians(_angle), glm::vec3(1.f, 0.f, 0.f));
    leftLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_leg_scale, y_leg_scale, z_leg_scale));
    leftLeg->_FT = leftLeg->_rot * leftLeg->_trs * leftLeg->_scale;
    leftLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, height * y_leg_scale, _pos));
    leftLeg->_FT = leftLeg->_trs * leftLeg->_FT;

    // 오른쪽 다리 변환
    rightLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(x_body_scale * width / 2 - width / 2 * x_leg_scale, -height / 2 * y_leg_scale, 0));
    rightLeg->_rot = glm::rotate(mat4(1.f), glm::radians(_angle), glm::vec3(-1.f, 0.f, 0.f));
    rightLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_leg_scale, y_leg_scale, z_leg_scale));
    rightLeg->_FT = rightLeg->_rot * rightLeg->_trs * rightLeg->_scale;
    rightLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, height * y_leg_scale, _pos));
    rightLeg->_FT = rightLeg->_trs * rightLeg->_FT;


    // 왼쪽 팔 변환
    leftArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-width / 2 * x_body_scale - width / 2 * x_arm_scale, -height / 2 * y_arm_scale, 0));
    leftArm->_rot = glm::rotate(mat4(1.f), glm::radians(_angle), glm::vec3(-1.f, 0.f, 0.f));
    leftArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_arm_scale, y_arm_scale, z_arm_scale));
    leftArm->_FT = leftArm->_rot * leftArm->_trs * leftArm->_scale;
    leftArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, height / 2 * y_arm_scale + height * y_leg_scale + height / 2 * y_body_scale, _pos));
    leftArm->_FT = leftArm->_trs * leftArm->_FT;

    // 오른쪽 팔 변환
    rightArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(width / 2 * x_body_scale + width / 2 * x_arm_scale, -height / 2 * y_arm_scale, 0));
    rightArm->_rot = glm::rotate(mat4(1.f), glm::radians(_angle), glm::vec3(1.f, 0.f, 0.f));
    rightArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_arm_scale, y_arm_scale, z_arm_scale));
    rightArm->_FT = rightArm->_rot * rightArm->_trs * rightArm->_scale;
    rightArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, height / 2 * y_arm_scale + height * y_leg_scale + height / 2 * y_body_scale, _pos));
    rightArm->_FT = rightArm->_trs * rightArm->_FT;

    // 머리 변환
    head->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, y_leg_scale * height + y_body_scale * height + y_head_scale * height / 2, _pos));
    head->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_head_scale, y_head_scale, z_head_scale));
    head->_FT = head->_trs * head->_scale;
}

extern bool render_aabb;
void Robot::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

		if (part->getCollider() != nullptr && m_bAlive && render_aabb)
		{
			part->getCollider()->renderAABB(shaderProgramID);
		}
    }
}

void Robot::OnCollisionEnter(Collider* _pOther)
{
	
}

void Robot::OnCollision(Collider* _pOther)
{
}

void Robot::OnCollisionExit(Collider* _pOther)
{
}

