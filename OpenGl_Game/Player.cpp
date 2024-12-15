#include "Player.h"
#include "Model.h"
#include "Gun.h"
#include "RPG.h"
#include "ShotGun.h"
#include "Rifle.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Healpack.h"
#include "Collider.h"
#include "func.h"

Player::Player() : _curgun(nullptr) {
    // �÷��̾��� ������ �߰��մϴ�.
    Cube* body = new Cube();
    Cube* head = new Cube();

    addPart(body);
    addPart(head);
	_objectpos = CameraManager::getInstance().getPosition();
    _hp = 5;

	_curgun = new Rifle();
	SceneManager::getInstance().AddObject(_curgun, GROUP_TYPE::GUN);

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
   
	//_curgun->update(deltaTime);
}

void Player::draw(GLuint shaderProgramID)
{
	//_curgun->draw(shaderProgramID);
}

void Player::setGun(int a) {
    DeleteObject(_curgun);
    if(a == 0)
	{
		_curgun = new Rifle();
		
	}
	else if (a == 1)
	{
		_curgun = new ShotGun();
	}
	else if (a == 2)
	{
		_curgun = new RPG();
	}
	SceneManager::getInstance().AddObject(_curgun, GROUP_TYPE::GUN);
}

Gun* Player::getGun() const {
    return _curgun;
}

void Player::OnCollisionEnter(Collider* _pOther)
{

}

