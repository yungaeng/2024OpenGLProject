// RPGProjectile.h
#pragma once

#include "Object.h"

class GLU_Object;

class RPGProjectile : public Object {
public:
    RPGProjectile(vec3 position, vec3 direction, float speed, float damage);
    virtual ~RPGProjectile();

    void update(float deltaTime) override;
    void draw(GLuint shaderProgramID) override;
    virtual void OnCollisionEnter(Collider* _pOther) override;

    float getDamage() const;
    void setDamage(float damage);

private:
    vec3 _direction;
    Cube* _body;
    GLU_Object* _glu_exp;
    float _speed;
    float _damage;
    float _range;
    float _traveledDistance;
    float _explosionRadius;
    float _exduration;
};
