
// SceneManager.cpp
#include "SceneManager.h"
#include "Object.h"
#include "global.h"
#include "Player.h"

void SceneManager::ResistPlayer(Player* player)
{
	_player = player;
}

void SceneManager::AddObject(Object* object) {
    objects.push_back(object);
}

void SceneManager::RemoveObject(Object* object) {
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void SceneManager::DrawObjects(GLuint shaderProgramID) {
    for (auto& object : objects) 
    {

    }
}

void SceneManager::update(float deltaTime)
{
	for (auto& object : objects)
	{
		object->update(deltaTime);
	}
}

void SceneManager::draw(GLuint shaderProgramID)
{
	for (auto& object : objects)
	{
		object->draw(shaderProgramID);
	}
}
