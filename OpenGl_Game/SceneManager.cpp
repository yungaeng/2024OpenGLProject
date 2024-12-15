// SceneManager.cpp
#include "SceneManager.h"
#include "Object.h"
#include "Player.h"
#include "Healpack.h"
#include "Monster.h"
#include "Robot.h"
#include "Bat.h"
#include <algorithm>


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



void SceneManager::update(float deltaTime)
{
	if (endTime > 120 || _player->GetHP() <= 0)
	{
		// 게임 종료
		exit(0);
	}
	// 몬스터 스폰 타이머 업데이트
	monsterSpawmTimer += deltaTime;
	if (monsterSpawmTimer >= MONSTER_SPAWN_INTERVAL) {
		spawnMonsters();
		monsterSpawmTimer = 0.0f;
	}
	// Healpack 스폰 타이머 업데이트
	healpackSpawnTimer += deltaTime;
	if (healpackSpawnTimer >= HEALPACK_SPAWN_INTERVAL) {
		spawnHealpack();
		healpackSpawnTimer = 0.0f;
	}
	endTime += deltaTime;

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

// 몬스터 스폰 메소드
void SceneManager::spawnMonsters() {
	std::uniform_int_distribution<int> numDist(4, 7);
	int numMonsters = numDist(rng);

	std::uniform_int_distribution<int> typeDist(1, 2);
	std::uniform_real_distribution<float> xDist(-3.0f, 3.0f);
	
	for (int i = 0; i < numMonsters; ++i) {
		int monsterType = typeDist(rng);
		Object* monster = nullptr;

		glm::vec3 position(xDist(rng), 0.f, -15.0f);

		if (monsterType == 1) {
			monster = new Robot();
		}
		else if (monsterType == 2) {
			monster = new Bat();
		}

		if (monster != nullptr) {
			AddObject(monster, GROUP_TYPE::MONSTER);
		}
	}
}

void SceneManager::spawnHealpack()
{
	std::uniform_real_distribution<float> xDist(-3.0f, 3.0f);
	std::uniform_real_distribution<float> zDist(-3.0f, 3.0f);

	glm::vec3 position(xDist(rng), 0.f, zDist(rng));
	Healpack* healpack = new Healpack();
	
	AddObject(healpack, GROUP_TYPE::ITEM);
}

void SceneManager::draw(GLuint shaderProgramID)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<Object*>::iterator iter = _objects[i].begin();
		for (; iter != _objects[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->draw(shaderProgramID);
				++iter;
			}
			else
			{
				iter = _objects[i].erase(iter);
			}
		}
	}

}






