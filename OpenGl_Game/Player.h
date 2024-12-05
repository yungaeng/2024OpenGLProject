#pragma once
#include "Object.h"

class Gun;

class Player : public Object {
public:
    Player();
    virtual void update(float deltaTime) override;
    void setGun(Gun* gun);
    Gun* getGun() const;

private:
    Gun* gun;
};
