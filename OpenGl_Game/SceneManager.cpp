
// SceneManager.cpp
#include "global.h"

#include "SceneManager.h"
#include "Object.h"
#include "Player.h"

void SceneManager::ResistPlayer(Player* player)
{
	_player = player;
}

void SceneManager::AddObject(Object* object, GROUP_TYPE _eType)
{
	_objects[(UINT)_eType].push_back(object);
}

void SceneManager::RemoveObject(Object* object) {
	for (auto& objects : _objects)
		objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void SceneManager::DrawObjects(GLuint shaderProgramID) {
    for (auto& object : _objects)
    {

    }
}

void SceneManager::update(float deltaTime)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < _objects[i].size(); ++j)
		{
			if (!_objects[i][j]->IsDead())
			{
				_objects[i][j]->update(deltaTime);
			}
		}
	}
}

void SceneManager::draw(GLuint shaderProgramID)
{
	for (auto& object : _objects)
	{
		for (auto& obj : object)
			obj->draw(shaderProgramID);
	}
}
