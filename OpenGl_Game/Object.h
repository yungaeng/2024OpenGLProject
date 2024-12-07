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

    virtual void update(float deltaTime);
    virtual void draw(GLuint shaderProgramID) = 0;
    bool IsDead() { return !m_bAlive; }
    void SetDead() { m_bAlive = false; }
	vec3 getPos() { return _objectpos; }

    // 충돌 시점 함수 목록 - 오브젝트가 처리할 충돌
    virtual void OnCollision(Collider* _pOther) {}		// 충돌 중인 경우 호출되는 함수
    virtual void OnCollisionEnter(Collider* _pOther) {}	// 충돌에 막 진입한 경우 호출되는 함수
    virtual void OnCollisionExit(Collider* _pOther) {}
protected:
    std::vector<Cube*> _parts;
	string _name;
    vec3 _objectpos;   // 오브젝트 중앙의 포지션
    bool m_bAlive;

};

