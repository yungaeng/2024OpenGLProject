// SceneManager.h
#pragma once
#include <vector>
class Object;

using GLuint = unsigned int;

class SceneManager {
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }
    void AddObject(Object* object);
    void RemoveObject(Object* object);
    void DrawObjects(GLuint shaderProgramID);
	void update(float deltaTime);
	void draw(GLuint shaderProgramID);

private:
    std::vector<Object*> objects;
};

