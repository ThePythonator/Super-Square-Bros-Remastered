#include "Player.hpp"

PlayerTest::PlayerTest() : PhysicsEntity() {

}

PlayerTest::PlayerTest(Framework::Spritesheet* _spritesheet_ptr) : PhysicsEntity(GAME::PHYSICS::PLAYER_PHYSICS_ENTITY_CONSTANTS), spritesheet_ptr(_spritesheet_ptr) {
	rect = Rect(128, 16, 8, 8); // Just for testing
}

void PlayerTest::update(float dt) {
	//PhysicsEntity::update(dt);
}

void PlayerTest::render() const {
	spritesheet_ptr->sprite(204, rect.position); // Just for testing
}