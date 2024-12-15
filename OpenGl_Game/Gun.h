// Gun.h
#pragma once

#include "Object.h"
enum gun_part {
	GUN_BODY,
	GUN_BARREL,
	GUN_STOCK,
	GUN_MAGAZINE,
	GUN_SCOPE
};
class Player;

class Gun : public Object {
public:
    Gun();
	virtual ~Gun();
public:
    virtual void update(float deltaTime) override = 0;
	virtual void Shoot() = 0;
	virtual void OnCollisionEnter(Collider* _pOther) = 0;
public:
	void draw(GLuint shaderProgramID) override = 0;
public:
	// gun stats
	vec3 _target;
	std::unique_ptr<Player> _player;
	unsigned int _damage;
	float _recoil;
	float _accuracy;
	float _range;
	float _reloadTimer;
	float _fireTimer;
};
