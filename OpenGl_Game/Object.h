#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Model.h"

using glm::vec3;

using GLuint = unsigned int;


class Object {

public:
    Object();
    virtual ~Object();

    void addPart(Cube* part);

    virtual void update(float deltaTime) = 0;
    virtual void draw(GLuint shaderProgramID) = 0;

protected:
    std::vector<Cube*> parts;
    vec3 _objectpos;   // 오브젝트 중앙의 포지션
};

