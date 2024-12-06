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
    void AddObject(Object* object);
    void RemoveObject(Object* object);
    void DrawObjects(GLuint shaderProgramID);
	void update(float deltaTime);
	void draw(GLuint shaderProgramID);

private:
    std::vector<Object*> objects;
	Player* _player;
};

