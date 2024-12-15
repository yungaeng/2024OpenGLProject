// GLU_Object.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <GL/glew.h>

class GLU_Object  {
public:
    GLU_Object();
    virtual ~GLU_Object();

    void setTranslation(const glm::mat4& trs);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(const glm::vec3& scale);
    void setCenter(const glm::vec3& center);
    void setFT();
    void draw(GLuint shaderProgramID);
	
private:
    void initSphere(float radius, unsigned int rings, unsigned int sectors);

    glm::mat4 _trs;
    glm::mat4 _rot;
    glm::mat4 _scale;
    glm::mat4 _FT;
    glm::vec4 _center;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;

};