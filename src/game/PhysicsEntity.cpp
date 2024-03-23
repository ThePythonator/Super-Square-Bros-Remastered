#include "PhysicsEntity.hpp"

PhysicsEntity::PhysicsEntity() : Entity() {

}

PhysicsEntity::PhysicsEntity(GAME::PHYSICS::PhysicsEntityConstants _constants) : Entity(), constants(_constants) {
	
}

//void PhysicsEntity::update(float dt) {
//
//}

//void PhysicsEntity::render() {
	// NOTE: RENDERING SHOULD NOT BE DONE IN THIS CLASS. INSTEAD IT NEEDS TO BE HANDLED BY THE INDIVIDUAL SUBCLASS, SINCE
	// THAT WILL HAVE ALL THE STATES AND CORRESPONDING ANIMATIONS NEEDED
	
	// TODO: render, but set flag to be l/r
	// pick transform based on last_direction

	// TODO: Need to handle this using an AnimationInterface for each state
	// e.g. running, idle, attacking - each one may have multiple animation frames so needs an AnimationHandler
//}

// Calculates and updates the last_direction variable
void PhysicsEntity::update_last_direction() {
	// Update last_direction
	if (velocity.x < 0) last_direction.x = -1;
	else if (velocity.x > 0) last_direction.x = 1;

	if (velocity.y < 0) last_direction.y = -1;
	else if (velocity.y > 0) last_direction.y = 1;
}

Framework::vec2 PhysicsEntity::get_velocity() const {
	return velocity;
}

Framework::vec2 PhysicsEntity::get_acceleration() const {
	return acceleration;
}

void PhysicsEntity::set_velocity(const Framework::vec2 _velocity) {
	velocity = _velocity;
}

void PhysicsEntity::set_acceleration(const Framework::vec2 _acceleration) {
	acceleration = _acceleration;
}

bool PhysicsEntity::is_collidable() const {
	return collidable;
}

void PhysicsEntity::set_collidable(bool _collidable) {
	collidable = _collidable;
}

const GAME::PHYSICS::PhysicsEntityConstants PhysicsEntity::get_constants() const {
	return constants;
}