#pragma once
#include "Object.h"

class Gun;

class Player : public Object {
public:
    Player();
	virtual ~Player();
    virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;
    void setGun(Gun* gun);
    
    Gun* getGun() const;

private:
    vector<Gun*> _Guns;
    Gun* _curgun;
    int _hp;
};
