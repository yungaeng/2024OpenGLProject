// Rocket.h
#pragma once
#include "Object.h"
class Gun;

class RPG : public Gun {
public:
    RPG();
    virtual ~RPG();

    void update(float deltaTime) override;
    void draw(GLuint shaderProgramID) override;
    float getDamage() { return _damage; }
    void setDamage(float damage) { _damage = damage; }
    void Shoot();

    virtual void OnCollisionEnter(Collider* _pOther) override;

private:
    vec3 _direction;
    Cube* _body;
    float _speed;
    float _damage;
    float _range;
    float _traveledDistance;
	float _fireTimer;
    float _explosionRadius; // Æø¹ß ¹üÀ§
};
