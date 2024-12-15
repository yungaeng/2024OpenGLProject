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
	/*for (auto& part : _parts) {
		if (part != nullptr)
			delete part;
	}
	_parts.clear();*/
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
    if (!_parts.empty()) {
        vec3 centroid(0.0f);
        for (auto& part : _parts) {
            // ������ ��ȯ ��Ŀ��� ��ġ�� �����մϴ�.
            // glm�� �� �켱(column-major) ����Դϴ�.
            vec3 position = vec3(part->_FT[3][0], part->_FT[3][1], part->_FT[3][2]);
            centroid += position;
        }
        centroid /= static_cast<float>(_parts.size());
        _objectpos = centroid;
    }
}
vec3 Object::getObjectPos()
{
	return _objectpos;
}


