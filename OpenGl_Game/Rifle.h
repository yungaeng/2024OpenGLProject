// Rifle.h
#pragma once
#include "Gun.h"



class Rifle : public Gun {
public:
    Rifle();
    virtual ~Rifle();

    void update(float deltaTime) override;
    void Shoot() override;
    void draw(GLuint shaderProgramID) override;

private:
    void reload();
    void handleRecoil();
};