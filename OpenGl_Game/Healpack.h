// Healpack.h
// 1209 ���� �߰�
#pragma once
#include "Item.h"


class Healpack : public Item {
public:
    Healpack();
    virtual ~Healpack();

    virtual void update(float deltaTime) override;
    virtual void draw(GLuint shaderProgramID) override;
    virtual void OnCollisionEnter(Collider* _pOther) override;
    virtual void OnCollision(Collider* _pOther) override;
    virtual void OnCollisionExit(Collider* _pOther) override;
    
    bool isOutOfRange() const;
private:
    // ����� �߰������� ���� �� ���ڰ� ���
    Cube* body;
    Cube* cross;

	float random_xpos;
    float zpos;

    void initializeParts();
    void updatePartTransforms();
    float _range = 100.f;
    float _traveledDistance = 0.f;
};
