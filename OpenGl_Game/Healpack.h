// Healpack.h
// 1209 힐팩 추가
#pragma once
#include "Item.h"


class Healpack : public Item {
public:
    Healpack();
    virtual ~Healpack();

    virtual void update(float deltaTime) override;
    virtual void draw(GLuint shaderProgramID) override;

private:
    // 몸통과 중간몸통을 구성 된 십자가 모양
    Cube* body;
    Cube* cross;

    void initializeParts();
    void updatePartTransforms();
};
