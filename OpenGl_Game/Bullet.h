// Bullet.h
#pragma once
#include "Object.h"

class Bullet : public Object {
public:
    Bullet(vec3 position, vec3 direction, float speed, float damage);
    virtual ~Bullet();

    void update(float deltaTime) override;
    void draw(GLuint shaderProgramID) override;
	float getDamage() { return _damage; }
	void setDamage(float damage) { _damage = damage; }
    bool isOutOfRange() const;

    virtual void OnCollisionEnter(Collider* _pOther) override;

private:
    vec3 _direction;
    Cube* _body;
    float _speed;
    float _damage;
    float _range;
    float _traveledDistance;
};

