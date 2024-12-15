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
            // 파츠의 변환 행렬에서 위치를 추출합니다.
            // glm은 열 우선(column-major) 행렬입니다.
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


