// ShotGun.cpp
#include "global.h"
#include "ShotGun.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "Bullet.h"
#include "SceneManager.h"

ShotGun::ShotGun() {
    // ShotGun Ư���� ���� �ʱ�ȭ
    _damage = 70;
    _recoil = 0.5f;
    _accuracy = 0.7f;
    _range = 50.0f;
    _reloadTimer = 2.5f;
    _fireTimer = 1.0f;

    Cube* cross;
    addPart(new Cube("Barrel"));    // �ѿ�
    addPart(new Cube("Body"));      // ��ü
    addPart(cross = new Cube("CrossLine")); // ���ڼ�
    cross->setColor(vec3(1.f, 1.f, 1.f));

    for (auto& part : _parts)
    {
        part->_owner = this;
        if (part->_name != "CrossLine")
            part->initCollider();
    }
}

ShotGun::~ShotGun() {
    // �ʿ��� ��� ���� �ڵ� �ۼ�
    for (auto& part : _parts) {
        delete part;
    }
}

void ShotGun::update(float deltaTime) {
    // ī�޶� ��ġ ������Ʈ
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    mat4 model = mat4(1.f);

    if (MouseManager::getInstance().IsLeftButtonPressed() && _fireTimer <= 0) {
        // �߻�
        Shoot();
        _fireTimer = 1.0f;
    }
    else {
        _fireTimer -= deltaTime;
    }

    for (auto& part : _parts) {
        if (part->_name == "Body")
        {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.15f, 0.15f, 1.0f));
        }
        else if (part->_name == "Barrel")
        {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            vec3 fronttrs = glm::normalize(cameraFront) * 0.5f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs + fronttrs);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.1f, 0.1f, 0.5f));
        }
        else if (part->_name == "CrossLine")
        {
            // ��ġ ��ȯ
            part->_trs = glm::translate(model, cameraPos);
            part->_trs = glm::translate(part->_trs, glm::normalize(cameraFront) * 0.3f);

            // ȸ�� ��ȯ
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // ������ ��ȯ
            part->_scale = glm::scale(mat4(1.f), vec3(0.005f, 0.00325f, 0.005f));
        }

        // ���� ��ȯ ��� ���
        part->_FT = part->_trs * part->_rot * part->_scale;

        // �浹ü ������Ʈ
        if (part->_collider != nullptr) {
            part->updateCollider();
        }
    }
}

void ShotGun::Shoot() {
    // ������ ���� ���� źȯ�� �۶߷� �߻�
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
	glm::normalize(cameraRight);
	glm::normalize(cameraUp);
	glm::normalize(cameraFront);
    vec3 bulletPos = cameraPos + cameraFront * 0.5f + cameraRight * 0.25f + cameraUp * -0.2f;

    int pelletCount = 8; // ���� źȯ ��
    float spreadAngle = 15.0f; // ź���� ����

    for (int i = 0; i < pelletCount; ++i) {
        // �������� ź���� �۶߸���
        float angleX = ((rand() % 100) / 100.0f - 0.5f) * spreadAngle;
        float angleY = ((rand() % 100) / 100.0f - 0.5f) * spreadAngle;
        vec3 direction = glm::rotate(mat4(1.0f), glm::radians(angleX), cameraUp) * vec4(cameraFront, 0.0f);
        direction = glm::rotate(mat4(1.0f), glm::radians(angleY), cameraRight) * vec4(direction, 0.0f);
        direction = glm::normalize(vec3(direction));

        Bullet* bullet = new Bullet(bulletPos, direction, 20.f, 5.f);
        bullet->setDamage(_damage);
        CreateObject(bullet, GROUP_TYPE::PROJ_PLAYER);
    }
}

void ShotGun::draw(GLuint shaderProgramID) {
    this->update(0);
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);
    }
}

void ShotGun::OnCollisionEnter(Collider* _pOther)
{
    // �ʿ��� ��� �浹 ó�� �ڵ� �ۼ�
}

void ShotGun::reload() {
    // ������ ���� ����
}
