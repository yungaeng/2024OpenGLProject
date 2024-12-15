// RPG.cpp
#include "global.h"
#include "Gun.h"
#include "RPG.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "RPGProjectile.h"
#include "SceneManager.h"

RPG::RPG() {
    // RPG Ư���� ���� �ʱ�ȭ
    _damage = 150;
    _range = 200.0f;
    _fireTimer = 1.5f;

    Cube* cross;
    addPart(new Cube("Barrel"));    // �ѿ�
    addPart(new Cube("Body"));      // ��ü
    addPart(cross = new Cube("CrossLine")); // ���ڼ�
    cross->setColor(vec3(1.f, 0.f, 0.f));

    for (auto& part : _parts) {
        part->_owner = this;
        if (part->_name != "CrossLine")
            part->initCollider();
    }
}

RPG::~RPG() {
    for (auto& part : _parts) {
        delete part;
    }
}

void RPG::update(float deltaTime) {
    // ī�޶� ��ġ ������Ʈ
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    mat4 model = mat4(1.f);

    if (MouseManager::getInstance().IsLeftButtonPressed() && _fireTimer <= 0) {
        // �߻�
        Shoot();
        _fireTimer = 1.5f; // ������ �ð� ����
    }
    else {
        _fireTimer -= deltaTime;
    }

    for (auto& part : _parts) {
        if (part->_name == "Body") {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.3f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.2f, 0.2f, 1.2f));
        }
        else if (part->_name == "Barrel") {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.3f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            vec3 fronttrs = glm::normalize(cameraFront) * 0.6f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs + fronttrs);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.15f, 0.15f, 0.6f));
        }
        else if (part->_name == "CrossLine") {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            part->_trs = glm::translate(part->_trs, glm::normalize(cameraFront) * 0.35f);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.005f, 0.00325f, 0.005f));
        }

        // ���� ��ȯ ��� ���
        part->_FT = part->_trs * part->_rot * part->_scale;

        // �浹ü ������Ʈ
        if (part->_collider != nullptr) 
        {
            part->updateCollider();
        }
    }
}

void RPG::Shoot() {
    // RPG �߻� ���� ����
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    vec3 rocketPos = cameraPos + cameraFront * 0.6f + cameraRight * 0.3f + cameraUp * -0.2f;
    vec3 direction = glm::normalize(cameraFront);

	// RPG �߻�
	//Bullet* bullet = new Bullet(rocketPos, direction, 30.f, _damage);
	//CreateObject(bullet, GROUP_TYPE::PROJ_PLAYER);
    RPGProjectile* rocket = new RPGProjectile(rocketPos, direction, 30.f, _damage);
    CreateObject(rocket, GROUP_TYPE::PROJ_PLAYER);
}

void RPG::draw(GLuint shaderProgramID) {
    this->update(0);
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);
    }
}

void RPG::OnCollisionEnter(Collider* _pOther) {
    // �ʿ��� ��� �浹 ó�� �ڵ� �ۼ�
}

