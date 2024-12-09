// Item.h
#pragma once
#include "Object.h"

class Item : public Object {
public:

	Item();
	virtual void update(float deltaTime) override;
	virtual void draw(GLuint shaderProgramID) override;

private:
	string			_name;
	unsigned int	_value;
};
