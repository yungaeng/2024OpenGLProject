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
    // 그냥 반환하면 복사해서 반환하기 때문에 복사비용이 추가됨, 따라서 원본 자체를 준다but 수정불가const
    const vector<Object*>& GetGroupObject(GROUP_TYPE _eType) { return _objects[(UINT)_eType]; }

private:
    std::vector<Object*> _objects[(unsigned int)GROUP_TYPE::END];
	Player* _player;
};

