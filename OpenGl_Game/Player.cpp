#include "Player.h"
#include "Model.h"
#include "Gun.h"

Player::Player() : gun(nullptr) {
    // �÷��̾��� ������ �߰��մϴ�.
    Cube* body = new Cube();
    Cube* head = new Cube();
    addPart(body);
    addPart(head);
}

void Player::update(float deltaTime) {
    // �÷��̾��� ������Ʈ ������ ���⿡ �߰��մϴ�.B
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

