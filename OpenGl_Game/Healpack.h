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

private:
    // ����� �߰������� ���� �� ���ڰ� ���
    Cube* body;
    Cube* cross;

    void initializeParts();
    void updatePartTransforms();
};
