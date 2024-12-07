// SceneManager.h
#pragma once
#include <vector>
class Object;
class Player;

using GLuint = unsigned int;

class SceneManager {
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }
	void ResistPlayer(Player* player);
    void AddObject(Object* object, GROUP_TYPE _eType);
    void RemoveObject(Object* object);
    void DrawObjects(GLuint shaderProgramID);
	void update(float deltaTime);
	void draw(GLuint shaderProgramID);
    // �׳� ��ȯ�ϸ� �����ؼ� ��ȯ�ϱ� ������ �������� �߰���, ���� ���� ��ü�� �ش�but �����Ұ�const
    const vector<Object*>& GetGroupObject(GROUP_TYPE _eType) { return _objects[(UINT)_eType]; }

private:
    std::vector<Object*> _objects[(unsigned int)GROUP_TYPE::END];
	Player* _player;
};

