// SceneManager.h
#pragma once
#include "global.h"
#include <vector>
#include <random>
class Object;
class Player;

using GLuint = unsigned int;
enum class GROUP_TYPE;

class SceneManager {
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }
	void ResistPlayer(Player* player);
    void AddObject(Object* object, GROUP_TYPE _eType);
    void RemoveObject(Object* object);
	void update(float deltaTime);
    void draw(GLuint shaderProgramID);
	void spawnMonsters();
	void spawnHealpack();
	Player* getPlayer() { return _player; }
    // �׳� ��ȯ�ϸ� �����ؼ� ��ȯ�ϱ� ������ �������� �߰���, ���� ���� ��ü�� �ش�but �����Ұ�const
    const vector<Object*>& GetGroupObject(GROUP_TYPE _eType) { return _objects[(UINT)_eType]; }
private:
    std::vector<Object*> _objects[(unsigned int)GROUP_TYPE::END];
	Player* _player;
	float endTime = 0;

    float monsterSpawmTimer;
	const float MONSTER_SPAWN_INTERVAL = 6.0f;
	float healpackSpawnTimer;
	float HEALPACK_SPAWN_INTERVAL = 10.0f;

	std::mt19937 rng;
};

