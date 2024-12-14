// Monster.h
#pragma once
#include "Object.h"

class Monster : public Object {
public:

    Monster();
    virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;
	virtual void OnCollisionEnter(Collider* _pOther) override {};
	virtual void OnCollision(Collider* _pOther) override {};
	virtual void OnCollisionExit(Collider* _pOther) override {};
protected:
	string			_name;
	float			_speed;
	int	_hp;
	int	_attack;
	int	_defense;
};
