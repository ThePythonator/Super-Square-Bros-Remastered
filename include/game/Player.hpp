#pragma once

#include "Spritesheet.hpp"

#include "PhysicsEntity.hpp"

// TODO: Remove/adapt after testing
class PlayerTest : public PhysicsEntity {
public:
	PlayerTest();
	PlayerTest(Framework::Spritesheet* _spritesheet_ptr);

	void update(float dt);
	void render() const;

private:
	Framework::Spritesheet* spritesheet_ptr = nullptr;
};