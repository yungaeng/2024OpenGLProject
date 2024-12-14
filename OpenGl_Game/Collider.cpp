#include "global.h"
#include "Collider.h"
#include "Object.h"

UINT Collider::g_iNextID = 0;

Collider::Collider()
	:m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_iCol(0)
	, m_bActive(true)
{
}

Collider::Collider(const Collider& _origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(_origin.m_iCol)
	, m_bActive(_origin.m_bActive)
{
	// finalpos는 충돌체에서 알아서 계산이 될 테니 제외
}

Collider::~Collider()
{
}


void Collider::finalupdate()
{
	// Object의 위치를 따라간다.
	vec3 vObjectPos = m_pOwner->getPosition();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
	assert(0 <= m_iCol);
}

void Collider::renderAABB(GLuint shaderProgramID)
{
    // AABB의 8개 꼭지점 계산
    std::vector<glm::vec3> corners = {
        glm::vec3(_minAABB.x, _minAABB.y, _minAABB.z),
        glm::vec3(_maxAABB.x, _minAABB.y, _minAABB.z),
        glm::vec3(_maxAABB.x, _maxAABB.y, _minAABB.z),
        glm::vec3(_minAABB.x, _maxAABB.y, _minAABB.z),
        glm::vec3(_minAABB.x, _minAABB.y, _maxAABB.z),
        glm::vec3(_maxAABB.x, _minAABB.y, _maxAABB.z),
        glm::vec3(_maxAABB.x, _maxAABB.y, _maxAABB.z),
        glm::vec3(_minAABB.x, _maxAABB.y, _maxAABB.z),
    };

    // AABB를 구성하는 선의 인덱스
    std::vector<unsigned int> indices = {
        0, 1, 1, 2, 2, 3, 3, 0, // 아래 사각형
        4, 5, 5, 6, 6, 7, 7, 4, // 위 사각형
        0, 4, 1, 5, 2, 6, 3, 7  // 수직 연결
    };

    // VAO 및 VBO 설정
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // VAO 바인딩
    glBindVertexArray(VAO);

    // VBO에 데이터 업로드
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, corners.size() * sizeof(glm::vec3), corners.data(), GL_STATIC_DRAW);

    // EBO에 인덱스 업로드
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex Attribute 설정
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // 선 그리기 모드로 설정
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 색상 설정 (예: 녹색)
    GLint colorLoc = glGetUniformLocation(shaderProgramID, "objectColor");
    glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);

    // 변환 행렬 설정 (단위 행렬 사용)
    glm::mat4 model = glm::mat4(1.0f);
    GLint modelLoc = glGetUniformLocation(shaderProgramID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // 그리기
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    // 상태 복원
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);

    // VAO, VBO, EBO 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}



void Collider::OnCollision(Collider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}
void Collider::OnCollisionEnter(Collider* _pOther)
{
	++m_iCol;
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionExit(Collider* _pOther)
{
	--m_iCol;
	m_pOwner->OnCollisionExit(_pOther);
}
