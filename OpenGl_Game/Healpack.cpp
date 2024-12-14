

// Healpack.cpp
#include "Healpack.h"
#include "Collider.h"

Healpack::Healpack() {
    initializeParts();
}

Healpack::~Healpack() {
    delete body;
    delete cross;
}

void Healpack::initializeParts() {
    body = new Cube("body");
    cross = new Cube("cross");
	// color select
	body->setColor(glm::vec3(0.1f, 1.0f, 0.1f));
	cross->setColor(glm::vec3(0.1f, 1.0f, 0.1f));


    // Collider �ʱ�ȭ
    body->initCollider();
    cross->initCollider();

    addPart(body);
    addPart(cross);

    for (auto& a : _parts)
    {
        a->initCollider();
        a->_owner = this;
    }
}

// Healpack Ŭ������ ȸ�� ���¸� ������ ��� ���� �߰�
float rotationAngle = 0.0f;

void Healpack::update(float deltaTime) {
    // ������ ���� ������Ʈ
    updatePartTransforms();
    Object::update(deltaTime);

    // ȸ�� �ӵ� ���� (�ʴ� 70�� ȸ��)
    const float rotationSpeed = 70.f;

    // ���� ȸ���� ���
    rotationAngle += rotationSpeed * deltaTime;
    if (rotationAngle > 360.f) rotationAngle -= 360.f; // 360���� ������ �ʱ�ȭ

    // ���� ȸ��
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    body->_FT = body->_trs * body->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * body->_scale;

    cross->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    cross->_FT = cross->_trs * cross->_rot * glm::rotate(glm::mat4(1.f), glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * cross->_scale;
}

void Healpack::updatePartTransforms() {
    // ���� ��ȯ
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.3f, 0.5f, 0.3f));
    body->_FT = body->_trs * body->_scale;
   // �߰� ���� ��ȯ
    cross->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.3f, 2.f));
    cross->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.7f, 0.2f, 0.3f));
    cross->_FT = cross->_trs * cross->_scale;
}

void Healpack::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

		if (part->_collider != nullptr)
		{
			part->_collider->renderAABB(shaderProgramID);
		}
    }
}

