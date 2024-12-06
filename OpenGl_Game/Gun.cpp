// Gun.cpp
#include "Gun.h"
#include "Model.h"
#include "CameraManager.h"
#include "Player.h"

Gun::Gun() 
	: _target(CameraManager::getInstance().getTarget())
	, _damage(0)
	, _recoil(0)
	, _accuracy(0)
	, _range(0)
	, _reloadTimer(0)
	, _fireTimer(0)
{
}

Gun::~Gun()
{
}


