// Rifle.cpp
#include "Rifle.h"
#include "CameraManager.h"

Rifle::Rifle() {
    // Initialize rifle-specific stats
    _damage = 10;
    _recoil = 0.2f;
    _accuracy = 1.f;
    _range = 100.0f;
    _reloadTimer = 2.0f;
    _fireTimer = 0.1f;
	addPart(new Cube("Barrel"));    // Barrel
	addPart(new Cube("Body"));      // Body
	addPart(new Cube("CrossLine")); // Stock
}

Rifle::~Rifle() {
    // Cleanup if necessary
}

void Rifle::update(float deltaTime) {
    // Update rifle state
    
    // Handle other updates like recoil recovery
    
}

void Rifle::Shoot() {
	// Implement shooting logic
}

void Rifle::draw(GLuint shaderProgramID) {
    // 모델 행렬 초기화
    mat4 model = mat4(1.f);
    vec3 cameraPos = CameraManager::getInstance().getPosition();
    vec3 cameraFront = CameraManager::getInstance().getFrontVector();
    vec3 cameraUp = CameraManager::getInstance().getUpVector();
    vec3 cameraRight = glm::cross(cameraFront, cameraUp);
    for (auto& part : _parts) {
		if (part->_name == "Body")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
            part->_trs = glm::translate(part->_trs, sidetrs);
            part->_trs = glm::translate(part->_trs, downtrs);
            // 카메라의 시선 방향에 따라 회전 변환 적용
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));
            // 

            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.1f, 0.1f, 1.5f));

            // 전체 변환 행렬 구성
            part->_FT = part->_trs * part->_rot * part->_scale;

            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
            part->Draw(shaderProgramID);
        }
        else if (part->_name == "Barrel")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
            vec3 sidetrs = glm::normalize(cameraRight) * 0.25f;
            vec3 downtrs = glm::normalize(cameraUp) * -0.2f;
			vec3 fronttrs = glm::normalize(cameraFront) * 0.5f;
            part->_trs = glm::translate(part->_trs, sidetrs);
            part->_trs = glm::translate(part->_trs, downtrs);
			part->_trs = glm::translate(part->_trs, fronttrs);
            // 카메라의 시선 방향에 따라 회전 변환 적용
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));

            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.05f, 0.04f, 1.f));

            // 전체 변환 행렬 구성
            part->_FT = part->_trs * part->_rot * part->_scale;

            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
            part->Draw(shaderProgramID);
		}
        else if (part->_name == "CrossLine")
        {
            // 위치 변환
            part->_trs = glm::translate(model, cameraPos);
			part->_trs = glm::translate(part->_trs, glm::normalize(cameraFront) * 0.3f);

            // 카메라의 시선 방향에 따라 회전 변환 적용
            part->_rot = glm::inverse(glm::lookAt(vec3(0.f), cameraFront, cameraUp));
            // 스케일 변환
            part->_scale = glm::scale(mat4(1.f), vec3(0.005f, 0.00325f, 0.005f));
            // 전체 변환 행렬 구성
            part->_FT = part->_trs * part->_rot * part->_scale;
            glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
            part->Draw(shaderProgramID);
        }
    }
}

void Rifle::reload() {

}
