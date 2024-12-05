// Rifle.cpp
#include "Rifle.h"
#include "CameraManager.h"

Rifle::Rifle() {
    // Initialize rifle-specific stats
    _damage = 10;
    _recoil = 0.2f;
    _accuracy = 1.f;
    _range = 100.0f;
    _reloadTimer = 2.0f;
    _fireTimer = 0.1f;
	addPart(new Cube());    // Barrel
	addPart(new Cube());    // Body
	parts[GUN_BODY]->_position = CameraManager::getInstance().getPosition();
}

Rifle::~Rifle() {
    // Cleanup if necessary
}

void Rifle::update(float deltaTime) {
    // Update rifle state
    for (auto& part : parts) {
        // Draw each part of the rifle
        part->model_init_buffer();
    }
    // Handle other updates like recoil recovery
    handleRecoil();
}

void Rifle::Shoot() {
	// Implement shooting logic
}

void Rifle::draw(GLuint shaderProgramID) {
	for (auto& part : parts) {
		// Draw each part of the rifle
		part->Draw(shaderProgramID);
	}
    // Implement drawing logic
}

void Rifle::reload() {

}

void Rifle::handleRecoil() {
    // Implement recoil handling logic
}