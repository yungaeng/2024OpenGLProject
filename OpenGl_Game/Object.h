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
	vector<Cube*>& getParts() { return _parts; }
    virtual void OnCollisionEnter(Collider* _pOther) {}
    virtual void OnCollision(Collider* _pOther) {}
    virtual void OnCollisionExit(Collider* _pOther) {}
	void setObjectPos(vec3 pos) { _objectpos = pos; }
    vec3 getObjectPos();
protected:
    std::vector<Cube*> _parts;
	string _name;
    vec3 _objectpos;   // 오브젝트 중앙의 포지션
    bool m_bAlive;

};

