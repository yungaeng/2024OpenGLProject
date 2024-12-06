#include "Player.h"
#include "Model.h"
#include "Gun.h"
#include "CameraManager.h"

Player::Player() : _curgun(nullptr) {
    // �÷��̾��� ������ �߰��մϴ�.
    Cube* body = new Cube();
    Cube* head = new Cube();
    addPart(body);
    addPart(head);
	_objectpos = CameraManager::getInstance().getPosition();
    _hp = 0;
}

Player::~Player()
{// �÷��̾� ������ �����մϴ�.
	for (auto& part : parts) {
		delete part;
	}
	parts.clear();
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

