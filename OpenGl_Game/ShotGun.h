// ShotGun.h
#pragma once
#include "Gun.h"

class ShotGun : public Gun {
public:
    ShotGun();
    virtual ~ShotGun();

    void update(float deltaTime) override;
    void Shoot() override;
    void draw(GLuint shaderProgramID) override;
    virtual void OnCollisionEnter(Collider* _pOther) override;

private:
    void reload();
};
