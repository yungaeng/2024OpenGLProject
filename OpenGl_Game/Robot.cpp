

// Robot.cpp
#include "Robot.h"
#include "Collider.h"
#include "Bullet.h"
#include "func.h"

Robot::Robot() {
    initializeParts();
    _angle = 0.f;
	_theta = 90.f;
}

Robot::~Robot() {
    delete body;
    delete leftLeg;
    delete rightLeg;
    delete leftArm;
    delete rightArm;
    delete head;
}

void Robot::initializeParts() {
    body = new Cube("body");
    leftLeg = new Cube("leftleg");
    rightLeg = new Cube("rightleg");
    leftArm = new Cube("leftarm");
    rightArm = new Cube("rightarm");
    head = new Cube("head");
    // color select
	body->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	leftArm->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	rightArm->setColor(glm::vec3(0.0f, 0.0f, 1.0f));    
	leftLeg->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	rightLeg->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
	head->setColor(glm::vec3(0.0f, 0.0f, 1.0f));
    _hp = 100;

    addPart(body);
    addPart(leftLeg);
    addPart(rightLeg);
    addPart(leftArm);
    addPart(rightArm);
    addPart(head);

	for (auto& a : _parts)
	{
		a->initCollider();
		a->_owner = this;
	}
}

void Robot::update(float deltaTime) {
    // �κ��� ���� ������Ʈ
   
    if (_angle >= 45.f)
        _theta = -90.f;
	else if (_angle <= -45.f)
		_theta = +90.f;
	_angle += _theta * deltaTime;

    updatePartTransforms();
	Object::update(deltaTime);
    
}

void Robot::updatePartTransforms() {

	// �κ��� �� ������ ��ġ, ȸ��, �������� ������Ʈ�մϴ�.

	static float body_yoffset = 0.5f;
	static float leg_yoffset = 0.25f;
	mat4 model = mat4(1.f);

    // ���� ��ȯ
    body->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.8f, 0.f));
    body->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.75f, 0.75f, 0.35f));
    body->_FT = body->_trs * body->_scale;

    // ���� �ٸ� ��ȯ
    leftLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.25f, leg_yoffset, 0.f));
	leftLeg->_rot = glm::rotate(model, glm::radians(_angle), glm::vec3(1.f, 0.f, 0.f));
    leftLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.25f, 0.5f, 0.25f));
    leftLeg->_FT = leftLeg->_rot* leftLeg->_trs  *leftLeg->_scale;

    // ������ �ٸ� ��ȯ
    rightLeg->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.25f, leg_yoffset, 0.f));
    rightLeg->_rot = glm::rotate(model, glm::radians(_angle), glm::vec3(-1.f, 0.f, 0.f));
    rightLeg->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.25f, 0.5f, 0.25f));
    rightLeg->_FT = rightLeg->_rot * rightLeg->_trs * rightLeg->_scale;

    // ���� �� ��ȯ
    leftArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(-0.75f, 1.5f, 0.f));
    leftArm->_rot = glm::rotate(model, glm::radians(_angle), glm::vec3(-1.f, 0.f, 0.f));
    leftArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
    leftArm->_FT = leftArm->_trs * leftArm->_rot * leftArm->_scale;

    // ������ �� ��ȯ
    rightArm->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.75f, 1.5f, 0.f));
    rightArm->_rot = glm::rotate(model, glm::radians(_angle), glm::vec3(1.f, 0.f, 0.f));
    rightArm->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.5f, 1.f, 0.5f));
    rightArm->_FT = rightArm->_trs * rightArm->_rot * rightArm->_scale;

    // �Ӹ� ��ȯ
    head->_trs = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 2.0f, 0.f));
    head->_scale = glm::scale(glm::mat4(1.f), glm::vec3(0.75f, 0.75f, 0.75f));
    head->_FT = head->_trs * head->_scale;
}

void Robot::draw(GLuint shaderProgramID) {
    for (auto& part : _parts) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(part->_FT));
        part->Draw(shaderProgramID);

		/*if (part->getCollider() != nullptr)
		{
			part->getCollider()->renderAABB(shaderProgramID);
		}*/
    }
}

void Robot::OnCollisionEnter(Collider* _pOther)
{
	Object* otherObject = _pOther->GetCube()->_owner;
	if (dynamic_cast<Bullet*>(otherObject) != nullptr)
    {
		float damage = dynamic_cast<Bullet*>(otherObject)->getDamage();
        _hp -= static_cast<int>(damage);
		if (_hp <= 0)
		{
            DeleteObject(this);
		}
	}
}

void Robot::OnCollision(Collider* _pOther)
{
}

void Robot::OnCollisionExit(Collider* _pOther)
{
}

