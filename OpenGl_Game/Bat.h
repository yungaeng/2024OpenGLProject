// Bat.h
#pragma once

class Monster;

class Bat : public Monster {
public:
    Bat();
    virtual ~Bat();

    virtual void update(float deltaTime) override;
    void updatePartTransforms(float deltaTime);
    virtual void draw(GLuint shaderProgramID) override;

    virtual void OnCollisionEnter(Collider* _pOther) override;
    virtual void OnCollision(Collider* _pOther) override;
    virtual void OnCollisionExit(Collider* _pOther) override;

private:
    void initializeParts();


    Cube* body;
    Cube* leftWing;
    Cube* rightWing;

    float _flight_height;
	float _random_xpos;
	float _zpos;
    float _angle;
    float _theta;
};
