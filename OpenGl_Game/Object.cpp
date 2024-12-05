#include "Object.h"
#include "Model.h"



Object::Object()
{
}

Object::~Object()
{
    for (auto& part : parts) {
        delete part;
    }
}

void Object::addPart(Cube* part)
{
    parts.push_back(part);
}


