// Item.h
#pragma once
#include "Object.h"

class Item : public Object {
public:

	Item();
	virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;
	virtual void OnCollisionEnter(Collider* _pOther) override {};
	virtual void OnCollision(Collider* _pOther) override {};
	virtual void OnCollisionExit(Collider* _pOther) override {};

private:
	string			_name;
	unsigned int	_value;
};
