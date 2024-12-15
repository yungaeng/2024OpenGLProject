// Bat.cpp
#include "global.h"
#include "Monster.h"
#include "Bat.h"
#include "Collider.h"
#include "Bullet.h"
#include "func.h"
#include "SceneManager.h"
#include "Player.h"
Bat::Bat() {
    initializeParts();
    _angle = 0.f;
    _theta = 90.f;
	_flight_height = 1.1f;
	_random_xpos = Random_0_to_1f() * 5.5f - 3;
	_zpos = -10.f;
}

Bat::~Bat() {
    delete body;
    delete leftWing;
    delete rightWing;
    Object::~Object();
}

void Bat::initializeParts() {
    body = new Cube("body");
    leftWing = new Cube("leftWing");
    rightWing = new Cube("rightWing");

    body->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
    leftWing->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));
    rightWing->setColor(glm::vec3(Random_0_to_1f(), Random_0_to_1f(), Random_0_to_1f()));

    // ���� �߰�
    addPart(body);
    addPart(leftWing);
    addPart(rightWing);

    // �ݶ��̴� �ʱ�ȭ �� ������ ����
    for (auto& part : _parts) {
        part->initCollider();
        part->_owner = this;
    }

    _hp = 250; // ü�� ���� (����)
}

void Bat::update(float deltaTime) {
    // ���� ���� ������Ʈ (��: ���� ������)
    if (_angle >= 45.f)
        _theta = -90.f;
    else if (_angle <= -45.f)
        _theta = 90.f;
    _angle += _theta * deltaTime;

    
	if (_zpos > 5)
    {
		SetDead();
		DeleteObject(this);
		SceneManager::getInstance().getPlayer()->SetHp(SceneManager::getInstance().getPlayer()->GetHP() - 1);
	}

    updatePartTransforms(deltaTime);
    Object::update(deltaTime);
}

void Bat::updatePartTransforms(float deltaTime) {
    // �� ������ ��ġ, ȸ��, ������ ������Ʈ

	float width = 1.f;
	float height = 1.f;

    // ũ��
	float x_body_scale = 0.5f;
	float y_body_scale = 0.3f;
	float z_body_scale = 1.0f;

	float x_wing_scale = 0.4f;
	float y_wing_scale = 0.2f;
	float z_wing_scale = 1.0f;

	_zpos += deltaTime;
    // ���� ��ȯ
	body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos, _flight_height, _zpos));
	body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_body_scale, y_body_scale, z_body_scale));
	body->_FT = body->_trs * body->_scale;

    // ���� ���� ��ȯ
    leftWing->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-width/2 * x_wing_scale,0.f,0.f));
	leftWing->_rot = glm::rotate(glm::mat4(1.f), glm::radians(_angle), glm::vec3(0.f, 0.f, 1.f));
	leftWing->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_wing_scale, y_wing_scale, z_wing_scale));
	leftWing->_FT = leftWing->_rot * leftWing->_trs * leftWing->_scale;
	leftWing->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos -width/2 * x_body_scale*1.1f, _flight_height, _zpos));
	leftWing->_FT = leftWing->_trs * leftWing->_FT;

    // ������ ���� ��ȯ
	rightWing->_trs = glm::translate(glm::mat4(1.f), glm::vec3(width / 2 * x_wing_scale, 0.f, 0.f));
	rightWing->_rot = glm::rotate(glm::mat4(1.f), glm::radians(-_angle), glm::vec3(0.f, 0.f, 1.f));
	rightWing->_scale = glm::scale(glm::mat4(1.f), glm::vec3(x_wing_scale, y_wing_scale, z_wing_scale));
	rightWing->_FT = rightWing->_rot * rightWing->_trs * rightWing->_scale;
	rightWing->_trs = glm::translate(glm::mat4(1.f), glm::vec3(_random_xpos+ width / 2 * x_body_scale*1.1f, _flight_height, _zpos));
	rightWing->_FT = rightWing->_trs * rightWing->_FT;
}
extern bool render_aabb;
void Bat::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

        if (part->getCollider() != nullptr && m_bAlive && render_aabb) {
            part->getCollider()->renderAABB(shaderProgramID);
        }
    }
}

void Bat::OnCollisionEnter(Collider* _pOther) {
  
}

void Bat::OnCollision(Collider* _pOther) {
    // �浹 ���� �� ���� (�ʿ� �� ����)
}

void Bat::OnCollisionExit(Collider* _pOther) {
    // �浹 ���� �� ���� (�ʿ� �� ����)
}
