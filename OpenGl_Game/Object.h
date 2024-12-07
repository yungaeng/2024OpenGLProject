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

    // �浹 ���� �Լ� ��� - ������Ʈ�� ó���� �浹
    virtual void OnCollision(Collider* _pOther) {}		// �浹 ���� ��� ȣ��Ǵ� �Լ�
    virtual void OnCollisionEnter(Collider* _pOther) {}	// �浹�� �� ������ ��� ȣ��Ǵ� �Լ�
    virtual void OnCollisionExit(Collider* _pOther) {}
protected:
    std::vector<Cube*> _parts;
	string _name;
    vec3 _objectpos;   // ������Ʈ �߾��� ������
    bool m_bAlive;

};

