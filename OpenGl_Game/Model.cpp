#define _CRT_SECURE_NO_WARNINGS
#include "Object.h"
#include "Model.h"`
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include "Collider.h"
#include "Robot.h"
#include "Gun.h"
#include "Bullet.h" 

float Random_0_to_1f_model() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

Model::Model()
    :
    _type(Model_Type::Type_non)
    , _trs(mat4(1.f))
    , _rot(mat4(1.f))
    , _scale(mat4(1.f))
    , _FT(mat4(1.f))
	, _position(vec3(0.f))
	, _collider(nullptr)

{
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenBuffers(6, EBOs);
}

Model::Model(Model_Type type)
    :
     _type(type)
    , _trs(mat4(1.f))
    , _rot(mat4(1.f))
    , _scale(mat4(1.f))
    , _FT(mat4(1.f))
	, _position(vec3(0.f))
    , _collider(nullptr)

{
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenBuffers(6, EBOs);
}

Model::~Model() {
	if (_collider != nullptr)
        delete _collider;
}


Cube::Cube()
    : Model(Model_Type::Type_cube)
    , _angle(0.f)
	, _xoffset(0.5f)
	, _yoffset(0.5f)
	, _zoffset(0.5f)
{
	// 큐브 모델 초기화
	read_obj_file("cube.obj", *this);
	_face_indices.resize(6);
	glGenVertexArrays(6, VAOs);
	glGenBuffers(6, VBOs);
	glGenBuffers(6, EBOs);
    _face_indices.resize(6);
  
}

Cube::Cube(string name)
    : Model(Model_Type::Type_cube)
    , _angle(0.f)
    , _xoffset(0.5f)
    , _yoffset(0.5f)
    , _zoffset(0.5f)
	, _name(name)
	, _maxAABB(vec3(0.f))
	, _minAABB(vec3(0.f))
	, _owner(nullptr)

{
    // 큐브 모델 초기화
    read_obj_file("cube.obj", *this);
    _face_indices.resize(6);
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenBuffers(6, EBOs);
    _face_indices.resize(6);

}

Cube::~Cube()
{
}



void Cube::model_init_buffer()
{
    if (_face_indices.size() != 6) {
        std::cerr << "Error: face indices size is not 6" << std::endl;
        exit(EXIT_FAILURE);
    }

    _vertices.clear();
    _indices.clear();

    for (auto& a : _face_indices)
        a.clear();

    int j = 0;
    size_t i = 0;
    for (i = 0; i < 6; i++) 
    {
        _face_indices[i].push_back(faces[j].v1);
        _face_indices[i].push_back(faces[j].v2);
        _face_indices[i].push_back(faces[j].v3);
        _face_indices[i].push_back(faces[++j].v1);
        _face_indices[i].push_back(faces[j].v2);
        _face_indices[i].push_back(faces[j].v3);
        ++j;
    }

    for (const auto& vertex : vertices) 
    {
        _vertices.push_back(vertex.x);
        _vertices.push_back(vertex.y);
        _vertices.push_back(vertex.z);
        _vertices.push_back(vertex.nx); // 노말 벡터 추가
        _vertices.push_back(vertex.ny); // 노말 벡터 추가
        _vertices.push_back(vertex.nz); // 노말 벡터 추가
        _vertices.push_back(vertex.r);
        _vertices.push_back(vertex.g);
        _vertices.push_back(vertex.b);
    }

    for (i = 0; i < _face_indices.size(); ++i) 
    {
        glBindVertexArray(VAOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _face_indices[i].size() * sizeof(unsigned int), _face_indices[i].data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void Cube::Draw(GLuint shaderProgramID)
{
    //_FT = _trs *_rot * _scale;
    model_init_buffer();

	if (_name == "CrossLine")
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // 앞면만 그리기
        glBindVertexArray(VAOs[5]); // 앞면에 해당하는 VAO 사용
        glDrawElements(GL_POLYGON, _face_indices[5].size(), GL_UNSIGNED_INT, 0);
    }

    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(shaderProgramID);

        for (int i = 0; i < _face_indices.size(); ++i)
        {
            glBindVertexArray(VAOs[i]);

            glDrawElements(GL_TRIANGLES, _face_indices[i].size(), GL_UNSIGNED_INT, 0);
        }
    }
}

void Cube::updateAABB()
{
    // 단위 큐브의 정점 좌표
    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    // 변환된 정점 좌표 계산
    std::vector<glm::vec3> transformedVertices;
    for (const auto& vertex : vertices) {
        glm::vec4 transformedVertex = _FT * glm::vec4(vertex, 1.0f);
        transformedVertices.push_back(glm::vec3(transformedVertex));
    }

    // AABB 초기화
    _minAABB = transformedVertices[0];
    _maxAABB = transformedVertices[0];

    // AABB 계산
    for (const auto& vertex : transformedVertices) {
        _minAABB = glm::min(_minAABB, vertex);
        _maxAABB = glm::max(_maxAABB, vertex);
    }
    _collider->SetAABB(_minAABB, _maxAABB);
}

void Cube::initCollider()
{

    _collider = new Collider();
    _collider->SetScale(vec3(1.0f));  // 기본 스케일 설정
    _collider->setOwner(this);
}

void Cube::updateCollider()
{
	if (_collider == nullptr)
		return;

    updateAABB();
    //// 월드 변환 행렬을 사용하여 AABB 계산
    //vec3 position = vec3(_FT * vec4(0.f, 0.f, 0.f, 1.f));
    //vec3 scale = vec3(_scale[0][0], _scale[1][1], _scale[2][2]) * _collider->GetScale();

    //vec3 halfScale = scale * 0.5f;
    //vec3 minAABB = position - halfScale;
    //vec3 maxAABB = position + halfScale;

    //_collider->SetAABB(minAABB, maxAABB);
    //_collider->SetFinalPos(position);
}

void Cube::OnCollision(Collider* _pOther)
{
	if (_owner != nullptr) {
		_owner->OnCollision(_pOther);
	}

}

void Cube::OnCollisionEnter(Collider* _pOther)
{
    if (_owner != nullptr) {
        _owner->OnCollisionEnter(_pOther);
        if (dynamic_cast<Bullet*>(_pOther->GetCube()->_owner) != nullptr && this->_name == "head")
		this->setColor(vec3(1.0f, 0.0f, 0.0f));
    }
}

void Cube::OnCollisionExit(Collider* _pOther)
{
	if (_owner != nullptr) {
		_owner->OnCollisionExit(_pOther);
	}
}

void Cube::setColor(vec3 color)
{
	for (auto& vertex : vertices) {
		vertex.r = color.r;
		vertex.g = color.g;
		vertex.b = color.b;
	}
}

Pyramid::Pyramid() : Model(Type_pyramid) {
    // 피라미드 모델 초기화
    read_obj_file("pyramid.obj", *this);
    _face_indices.resize(5);
    glGenVertexArrays(5, VAOs);
    glGenBuffers(5, VBOs);
    glGenBuffers(5, EBOs);
}

void Pyramid::model_init_buffer() {
    _vertices.clear();
    _indices.clear();

    int j = 0;
    size_t i = 0;
    for (auto& a : _face_indices)
        a.clear();
     for (i = 0; i < 5; i++) 
    {
        _face_indices[i].push_back(faces[j].v1);
        _face_indices[i].push_back(faces[j].v2);
        _face_indices[i].push_back(faces[j].v3);
        if (i == 4)
        {
            _face_indices[i].push_back(faces[++j].v1);
            _face_indices[i].push_back(faces[j].v2);
            _face_indices[i].push_back(faces[j].v3);
        }
        else
            ++j;
    }
    // 각 면의 정점 데이터를 _vertices에 저장
    for (const auto& vertex : vertices) {
        _vertices.push_back(vertex.x);
        _vertices.push_back(vertex.y);
        _vertices.push_back(vertex.z);
        _vertices.push_back(vertex.nx); // 노말 벡터 추가
        _vertices.push_back(vertex.ny); // 노말 벡터 추가
        _vertices.push_back(vertex.nz); // 노말 벡터 추가
        _vertices.push_back(vertex.r);
        _vertices.push_back(vertex.g);
        _vertices.push_back(vertex.b);
    }
    // 각 면에 대해 별도의 VAO, VBO, EBO를 바인딩하고 데이터를 버퍼에 올림
    for (i = 0; i < _face_indices.size(); ++i)
    {
        glBindVertexArray(VAOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _face_indices[i].size() * sizeof(unsigned int), _face_indices[i].data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}


void Pyramid::Draw(GLuint shaderProgramID) {
   
    glUseProgram(shaderProgramID);

    for (int i = 0; i < _face_indices.size(); ++i)
    {
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, _face_indices[i].size(), GL_UNSIGNED_INT, 0);
    }
}



void read_newline(std::string& str) {
    if (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }
}

void read_obj_file(const std::string& filename, Model& model) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (file.getline(line, MAX_LINE_LENGTH)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            Vertex vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            vertex.r = Random_0_to_1f_model();
            vertex.g = Random_0_to_1f_model();
            vertex.b = Random_0_to_1f_model();
            model.vertices.push_back(vertex);
        }
        else if (prefix == "vn") {
            vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            model.normals.push_back(normal);
        }
        else if (prefix == "f") {
            Face face;
            char slash;
            ss >> face.v1 >> slash >> slash >> face.n1
               >> face.v2 >> slash >> slash >> face.n2
               >> face.v3 >> slash >> slash >> face.n3;

            // 인덱스를 1 감소시켜 0부터 시작하도록 수정
            face.v1 -= 1;
            face.v2 -= 1;
            face.v3 -= 1;
            face.n1 -= 1;
            face.n2 -= 1;
            face.n3 -= 1;
            model.faces.push_back(face);
        }
    }


    // 각 정점에 대해 노멀 벡터의 평균을 계산하여 저장
    std::vector<std::vector<vec3>> vertex_normals(model.vertices.size());
    for (const auto& face : model.faces) {
        vertex_normals[face.v1].push_back(model.normals[face.n1]);
        vertex_normals[face.v2].push_back(model.normals[face.n2]);
        vertex_normals[face.v3].push_back(model.normals[face.n3]);
    }

    for (size_t i = 0; i < model.vertices.size(); ++i) {
        vec3 avg_normal(0.0f, 0.0f, 0.0f);
        for (const auto& normal : vertex_normals[i]) {
            avg_normal.x += normal.x;
            avg_normal.y += normal.y;
            avg_normal.z += normal.z;
        }
        avg_normal.x /= vertex_normals[i].size();
        avg_normal.y /= vertex_normals[i].size();
        avg_normal.z /= vertex_normals[i].size();

        model.vertices[i].nx = avg_normal.x;
        model.vertices[i].ny = avg_normal.y;
        model.vertices[i].nz = avg_normal.z;
    }
}