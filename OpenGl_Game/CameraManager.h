#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class KeyManager;

class CameraManager {
public:

    static CameraManager& getInstance() {
        static CameraManager instance;
        return instance;
    }
    CameraManager();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix() const;
    void update(KeyManager& keyManager, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void rotateLeft(float deltaTime);
    void rotateRight(float deltaTime);

    void setPerspective(bool isPerspective);
    void setAspectRatio(float ratio);
    void setFOV(float fieldOfView);
    void setNearPlane(float nnear);
    void setFarPlane(float ffar);
    glm::vec3 getTarget() {
        return target;
    };
	glm::vec3 getPosition() {
		return position;
	};

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 u; // Right vector
    glm::vec3 v; // Up vector
    glm::vec3 n; // Front vector
    float speed;
    float rotationSpeed;
    bool perspective;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    float yaw;
    float pitch;
    float sensitivity;
};
