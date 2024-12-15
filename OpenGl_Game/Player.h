#pragma once
#include "Object.h"

class Gun;

class Player : public Object {
public:
    Player();
	virtual ~Player();
    virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;
    void setGun(int a);
    
    Gun* getGun() const;

    // 12/15 hp 변경함수 추가
    void SetHp(int newhp) { _hp = newhp;  };
    int GetHP() const { return _hp; };

    // 12/15 충돌처리 추가
    virtual void OnCollisionEnter(Collider* _pOther) override;

private:
    vector<Gun*> _Guns;
    Gun* _curgun;
    int _hp;
};
