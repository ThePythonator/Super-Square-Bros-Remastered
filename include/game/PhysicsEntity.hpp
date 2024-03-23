#pragma once

#include "Maths.hpp"
#include "File.hpp"

#include "Constants.hpp"

#include "Entity.hpp"

// The actual physics is handled by PhysicsHandler
class PhysicsEntity : public Entity {
public:
	PhysicsEntity();
	PhysicsEntity(GAME::PHYSICS::PhysicsEntityConstants _constants);

	//void update(float dt);

	void update_last_direction();

	Framework::vec2 get_velocity() const;
	Framework::vec2 get_acceleration() const;

	void set_velocity(const Framework::vec2 _velocity);
	void set_acceleration(const Framework::vec2 _acceleration);

	bool is_collidable() const;
	void set_collidable(bool _collidable);

	const GAME::PHYSICS::PhysicsEntityConstants get_constants() const;

protected:
	// The position is stored as rect.position
	Framework::vec2 velocity, acceleration;

	// The last horizontal and vertical directions are stored
	Framework::vec2 last_direction = Framework::vec2{ 1, 1 };

	// Determines whether the entity can collide with platforms and other objects
	bool collidable = true; // TODO: confirm if needed

	GAME::PHYSICS::PhysicsEntityConstants constants;
};