#include "Player.h"
#include "Model.h"
#include "Gun.h"
#include "CameraManager.h"

Player::Player() : _curgun(nullptr) {
    // 플레이어의 파츠를 추가합니다.
    Cube* body = new Cube();
    Cube* head = new Cube();
    addPart(body);
    addPart(head);
	_objectpos = CameraManager::getInstance().getPosition();
    _hp = 0;
}

Player::~Player()
{// 플레이어 파츠를 삭제합니다.
	for (auto& part : parts) {
		delete part;
	}
	parts.clear();
}

void Player::update(float deltaTime) {
    // 플레이어의 업데이트 로직을 여기에 추가합니다.
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

