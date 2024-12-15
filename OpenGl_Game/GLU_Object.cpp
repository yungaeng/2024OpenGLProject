// GLU_Object.cpp
#include "GLU_Object.h"
#include "Object.h"
#include <cmath>
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

GLU_Object::GLU_Object()
    : _trs(glm::mat4(1.0f))
    , _rot(glm::mat4(1.0f))
    , _scale(glm::mat4(1.0f))
    , _FT(glm::mat4(1.0f))
    , _center(0.0f, 0.0f, 0.0f, 1.0f)
    , _vao(0)
    , _vbo(0)
    , _ebo(0)
{
    initSphere(1.0f, 32, 32);
	Cube* _Body = new Cube("Body");
	_Body->initCollider();
}

GLU_Object::~GLU_Object() {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void GLU_Object::setTranslation(const glm::mat4& trs  ) {
    _trs = trs;
    _center = _trs * _center;       // 중심 좌표에 변환 적용
}

void GLU_Object::setRotation(float angle, const glm::vec3& axis) {
    _rot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    _center = _rot * _center;       // 중심 좌표에 변환 적용
}

void GLU_Object::setScale(const glm::vec3& scale) {
    _scale = glm::scale(glm::mat4(1.0f), scale);
    _center = _scale * _center;     // 중심 좌표에 변환 적용
}

void GLU_Object::setCenter(const glm::vec3& center) {
    _center = glm::vec4(center, 1.0f);
}

void GLU_Object::setFT() {
    _FT = _trs * _rot * _scale;
}

void GLU_Object::initSphere(float radius, unsigned int rings, unsigned int sectors) {
    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);
    int r, s;

    _vertices.resize(rings * sectors * 3);
    std::vector<float>::iterator v = _vertices.begin();
    for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
        float const y = sin(-M_PI_2 + M_PI * r * R);
        float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
        float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

        *v++ = x * radius;
        *v++ = y * radius;
        *v++ = z * radius;
    }

    _indices.resize(rings * sectors * 4);
    std::vector<unsigned int>::iterator i = _indices.begin();
    for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
        *i++ = r * sectors + s;
        *i++ = r * sectors + (s + 1);
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
    }

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void GLU_Object::draw(GLuint shaderProgramID) {

    glUseProgram(shaderProgramID);

    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(_FT));

    glBindVertexArray(_vao);
    glDrawElements(GL_POLYGON, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

