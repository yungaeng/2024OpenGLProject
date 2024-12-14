#include "Player.h"
#include "Model.h"
#include "Gun.h"
#include "CameraManager.h"
#include "Healpack.h"
#include "Collider.h"

Player::Player() : _curgun(nullptr) {
    // �÷��̾��� ������ �߰��մϴ�.
    Cube* body = new Cube();
    Cube* head = new Cube();

    addPart(body);
    addPart(head);
	_objectpos = CameraManager::getInstance().getPosition();
    _hp = 0;

    body->initCollider();
}

Player::~Player()
{// �÷��̾� ������ �����մϴ�.
	for (auto& part : _parts) {
		delete part;
	}
    _parts.clear();
}

void Player::update(float deltaTime) {
    // �÷��̾��� ������Ʈ ������ ���⿡ �߰��մϴ�.
    _objectpos = CameraManager::getInstance().getPosition();

    if (_curgun) {
        _curgun->update(deltaTime);
    }

}

void Player::draw(GLuint shaderProgramID)
{
}

void Player::setGun(Gun* gun) {
    this->_curgun = gun;
}

Gun* Player::getGun() const {
    return _curgun;
}

void Player::OnCollisionEnter(Collider* _pOther)
{
    // �浹�� ��ü�� �����ڸ� �����ɴϴ�.
    Object* otherObject = _pOther->GetCube()->_owner;
    if (Healpack* healpack = dynamic_cast<Healpack*>(otherObject))
    {
        // �÷��̾��� ü���� ȸ���մϴ�
        SetHp(100);
    }
}

