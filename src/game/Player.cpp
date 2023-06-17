#include "Player.hpp"

PlayerTest::PlayerTest() : PhysicsEntity() {

}

PlayerTest::PlayerTest(Framework::Spritesheet* _spritesheet_ptr) : PhysicsEntity(), spritesheet_ptr(_spritesheet_ptr) {
	rect = Rect(64, 16, 8, 8); // Just for testing
}

void PlayerTest::update(float dt) {
	acceleration = Framework::Vec(0, 9.81);

	PhysicsEntity::update(dt);
}

void PlayerTest::render() const {
	spritesheet_ptr->sprite(0, rect.position); // Just for testing
}