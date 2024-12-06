// Robot.h
#pragma once
#include "Monster.h"


class Robot : public Monster {
public:
    Robot();
    virtual ~Robot();

    virtual void update(float deltaTime) override;
    virtual void draw(GLuint shaderProgramID) override;

private:
    Cube* body;
    Cube* leftLeg;
    Cube* rightLeg;
    Cube* leftArm;
    Cube* rightArm;
    Cube* head;

    void initializeParts();
    void updatePartTransforms();
};