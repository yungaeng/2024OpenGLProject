// Monster.h
#pragma once
#include "Object.h"

class Monster : public Object {
public:
    Monster();
    virtual void update(float deltaTime) override;

private:
	float			_speed;
	unsigned int	_hp;
	unsigned int	_attack;
	unsigned int	_defense;
};
