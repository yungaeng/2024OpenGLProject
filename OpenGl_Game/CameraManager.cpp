#include "CameraManager.h"
#include "KeyManager.h"

CameraManager::CameraManager()
    : position(0.0f, 0.65f, 5.0f),  // 카메라 위치 0.65로 설정 12.13
    target(0.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
	n(0.0f, 0.0f, -1.0f),
	u(1.0f, 0.0f, 0.0f),
    v(0.0f, 1.0f, 0.0f),
    speed(0.5f),
    rotationSpeed(5.f),
    perspective(true),
    fov(45.0f),
    aspectRatio(4.0f / 3.0f),
    nearPlane(0.1f),
    farPlane(100.0f),
    yaw(-90.0f), // 초기 yaw 값
    pitch(0.0f), // 초기 pitch 값
    sensitivity(0.1f)
{
}

glm::mat4 CameraManager::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 CameraManager::getProjectionMatrix() const {
    if (perspective) {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
    else {
        return glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, nearPlane, farPlane);
    }
}

void CameraManager::update(KeyManager& keyManager, float deltaTime) {
    if (keyManager.IsKeyPressed('w')) {
        moveForward(deltaTime);
    }
    if (keyManager.IsKeyPressed('s')) {
        moveBackward(deltaTime);
    }
    if (keyManager.IsKeyPressed('a')) {
        moveLeft(deltaTime);
    }
    if (keyManager.IsKeyPressed('d')) {
        moveRight(deltaTime);
    }
    if (keyManager.IsKeyPressed('p')) {
        setPerspective(true);
    }
    if (keyManager.IsKeyPressed('o')) {
        setPerspective(false);
    }
}

void CameraManager::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // 제한 각도 설정
    if (pitch > 20.0f)
        pitch = 20.0f;
    if (pitch < -20.0f)
        pitch = -20.0f;
	
	

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    direction = glm::normalize(direction);

	// up vector 계산
	u = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
	v = glm::normalize(glm::cross(u, direction));
	n = direction;
    target = position + direction;
}

void CameraManager::moveForward(float deltaTime) {
	glm::vec3 ntarget = glm::normalize(this->target - position);
    glm::vec3 direction = glm::normalize(ntarget);
    direction.y = 0;
    position += direction * speed * deltaTime;
    target += direction * speed * deltaTime;
}

void CameraManager::moveBackward(float deltaTime) {
    glm::vec3 direction = glm::normalize(glm::vec3(0.f, 0.f, -1.f));
    position -= direction * speed * deltaTime;
    target -= direction * speed * deltaTime;
}

void CameraManager::moveLeft(float deltaTime) {
    glm::vec3 direction = glm::normalize(glm::cross(up, target - position));
    position += direction * speed * deltaTime;
    target += direction * speed * deltaTime;
}

void CameraManager::moveRight(float deltaTime) {
    glm::vec3 direction = glm::normalize(glm::cross(up, target - position));
    position -= direction * speed * deltaTime;
    target -= direction * speed * deltaTime;
}

void CameraManager::rotateLeft(float deltaTime) {
    float angle = rotationSpeed * deltaTime;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), up);
    position = glm::vec3(rotation * glm::vec4(position - target, 1.0f)) + target;
}

void CameraManager::rotateRight(float deltaTime) {
    float angle = -rotationSpeed * deltaTime;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), up);
    position = glm::vec3(rotation * glm::vec4(position - target, 1.0f)) + target;
}

void CameraManager::setPerspective(bool isPerspective) {
    perspective = isPerspective;
}

void CameraManager::setAspectRatio(float ratio) {
    aspectRatio = ratio;
}

void CameraManager::setFOV(float fieldOfView) {
    fov = fieldOfView;
}

void CameraManager::setNearPlane(float nnear) {
    nearPlane = nnear;
}

void CameraManager::setFarPlane(float ffar) {
    farPlane = ffar;
}
