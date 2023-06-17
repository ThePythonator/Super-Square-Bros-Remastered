#pragma once

#include "Maths.hpp"

#include "Entity.hpp"

class PhysicsEntity : public Entity {
public:
	PhysicsEntity();
	PhysicsEntity(Rect _rect);

	void update(float dt);

protected:
	// The position is stored as rect.position
	Framework::vec2 velocity, acceleration;

	// The last horizontal and vertical directions are stored
	Framework::vec2 last_direction = Framework::vec2{ 1, -1 };

	// Determines whether the entity can collide with platforms and other objects
	bool is_collidable = true; // TODO: confirm if needed

private:
	void update_last_direction();
};