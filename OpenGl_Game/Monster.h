// Monster.h
#pragma once
#include "Object.h"

class Monster : public Object {
public:

    Monster();
    virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;

private:
	string			_name;
	float			_speed;
	unsigned int	_hp;
	unsigned int	_attack;
	unsigned int	_defense;
};
