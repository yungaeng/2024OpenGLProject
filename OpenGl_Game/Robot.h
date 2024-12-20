// Robot.h
#pragma once
#include "Monster.h"


class Robot : public Monster {
public:
    Robot();
    virtual ~Robot();

    virtual void update(float deltaTime) override;
    void updatePartTransforms(float deltaTime);
    virtual void draw(GLuint shaderProgramID) override;
	virtual void OnCollisionEnter(Collider* _pOther) override;
	virtual void OnCollision(Collider* _pOther) override;
	virtual void OnCollisionExit(Collider* _pOther) override;

private:
    Cube* body;
    Cube* leftLeg;
    Cube* rightLeg;
    Cube* leftArm;
    Cube* rightArm;
    Cube* head;
    float _angle;
    float _theta;
    float _pos;
    float _random_xpos;
    void initializeParts();

};