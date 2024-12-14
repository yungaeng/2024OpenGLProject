// Rifle.cpp
#include "global.h"
#include "Rifle.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "Bullet.h"
#include "SceneManager.h"

Rifle::Rifle() {
    // Initialize rifle-specific stats
    _damage = 10;
    _recoil = 0.2f;
    _accuracy = 1.f;
    _range = 100.0f;
    _reloadTimer = 2.0f;
    _fireTimer = 0.1f;
    Cube* cross;
	addPart(new Cube("Barrel"));    // Barrel
	addPart(new Cube("Body"));      // Body
	addPart(cross = new Cube("CrossLine")); // cross line
	cross->setColor(vec3(1.f, 1.f, 1.f));   

    for (auto& a : _parts)
	{
		a->_owner = this;
		if (a->_name != "CrossLine")
		    a->initCollider();
	}
}

Rifle::~Rifle() {
    // Cleanup if necessary
	for (auto& part : _parts) {
		delete part;
	}
}

void Rifle::update(float deltaTime) {
    // 카메라 정보 가져오기
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    mat4 model = mat4(1.f);

	if (MouseManager::getInstance().IsLeftButtonPressed() && _fireTimer <= 0) {
		// 총알 발사
		Shoot();
		_fireTimer = 0.1f;
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
            part->_scale = glm::scale(mat4(1.f), vec3(0.1f, 0.1f, 1.5f));
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
            part->_scale = glm::scale(mat4(1.f), vec3(0.05f, 0.04f, 1.f));
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

        // 전체 변환 행렬 구성
        part->_FT = part->_trs * part->_rot * part->_scale;

        // 콜라이더 업데이트
        if (part->_collider != nullptr) {
            part->updateCollider();
        }
    }
    // 기타 업데이트 로직 추가 가능   
}

void Rifle::Shoot() {
	// Implement shooting logic
	// 총알 생성
	vec3 cameraPos = CameraManager::getInstance().getPosition();
	vec3 cameraFront = CameraManager::getInstance().getFrontVector();
	vec3 cameraUp = CameraManager::getInstance().getUpVector();
	vec3 cameraRight = glm::cross(cameraFront, cameraUp);
	vec3 bulletPos = cameraPos + cameraFront * 0.5f + cameraRight * 0.25f + cameraUp * -0.2f;
	vec3 bulletDir = cameraFront;
	Bullet* bullet = new Bullet(bulletPos, bulletDir, 10.f, 10.f);
    bullet->setDamage(10.f);
	CreateObject(bullet, GROUP_TYPE::PROJ_PLAYER);


}

void Rifle::draw(GLuint shaderProgramID) {
    this->update(0);
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);
    }
}

void Rifle::OnCollisionEnter(Collider* _pOther)
{

}

void Rifle::reload() {

}
