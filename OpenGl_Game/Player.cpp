#include "Player.h"
#include "Model.h"
#include "Gun.h"

Player::Player() : gun(nullptr) {
    // 플레이어의 파츠를 추가합니다.
    Cube* body = new Cube();
    Cube* head = new Cube();
    addPart(body);
    addPart(head);
}

void Player::update(float deltaTime) {
    // 플레이어의 업데이트 로직을 여기에 추가합니다.B
    if (gun) {
        gun->update(deltaTime);
    }
}

void Player::setGun(Gun* gun) {
    this->gun = gun;
}

Gun* Player::getGun() const {
    return gun;
}

