#include "Object.h"
#include "Model.h"



Object::Object()
	: _objectpos(vec3(0.f))
	, m_bAlive(true)
	, _name("Object")
{
}

Object::~Object()
{
}

void Object::addPart(Cube* part)
{
    _parts.push_back(part);
}

void Object::update(float deltaTime)
{
    for (auto& part : _parts) {
        part->updateCollider();
    }
}


