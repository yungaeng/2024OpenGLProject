// ShotGun.cpp
#include "global.h"
#include "ShotGun.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "Bullet.h"
#include "SceneManager.h"

ShotGun::ShotGun() {
    // ShotGun 특유의 스탯 초기화
    _damage = 70;
    _recoil = 0.5f;
    _accuracy = 0.7f;
    _range = 50.0f;
    _reloadTimer = 2.5f;
    _fireTimer = 1.0f;

    Cube* cross;
    addPart(new Cube("Barrel"));    // 총열
    addPart(new Cube("Body"));      // 본체
    addPart(cross = new Cube("CrossLine")); // 십자선
    cross->setColor(vec3(1.f, 1.f, 1.f));

    for (auto& part : _parts)
    {
        part->_owner = this;
        if (part->_name != "CrossLine")
            part->initCollider();
    }
}

ShotGun::~ShotGun() {
    // 필요한 경우 정리 코드 작성
    for (auto& part : _parts) {
        delete part;
    }
}

void ShotGun::update(float deltaTime) {
    // 카메라 위치 업데이트
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    mat4 model = mat4(1.f);

    if (MouseManager::getInstance().IsLeftButtonPressed() && _fireTimer <= 0) {
        // 발사
        Shoot();
        _fireTimer = 1.0f;
    }
    else {
        _fireTimer -= deltaTime;
    }

    for (auto& part : _parts) {
        if (part->_name == "Body")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs);

            // 회전 변환
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.15f, 0.15f, 1.0f));
        }
        else if (part->_name == "Barrel")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            vec3 fronttrs = glm::normalize(cameraFront) * 0.5f;
            part->_trs = glm::translate(part->_trs, sidetrs + downtrs + fronttrs);

            // 회전 변환
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.1f, 0.1f, 0.5f));
        }
        else if (part->_name == "CrossLine")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
            part->_trs = glm::translate(part->_trs, glm::normalize(cameraFront) * 0.3f);

            // 회전 변환
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.005f, 0.00325f, 0.005f));
        }

        // 최종 변환 행렬 계산
        part->_FT = part->_trs * part->_rot * part->_scale;

        // 충돌체 업데이트
        if (part->_collider != nullptr) {
            part->updateCollider();
        }
    }
}

void ShotGun::Shoot() {
    // 샷건은 여러 개의 탄환을 퍼뜨려 발사
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
	glm::normalize(cameraRight);
	glm::normalize(cameraUp);
	glm::normalize(cameraFront);
    vec3 bulletPos = cameraPos + cameraFront * 0.5f + cameraRight * 0.25f + cameraUp * -0.2f;

    int pelletCount = 8; // 샷건 탄환 수
    float spreadAngle = 15.0f; // 탄착군 각도

    for (int i = 0; i < pelletCount; ++i) {
        // 무작위로 탄착군 퍼뜨리기
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
    // 필요한 경우 충돌 처리 코드 작성
}

void ShotGun::reload() {
    // 재장전 로직 구현
}
