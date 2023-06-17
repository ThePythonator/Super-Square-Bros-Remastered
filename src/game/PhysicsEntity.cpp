#include "PhysicsEntity.hpp"

PhysicsEntity::PhysicsEntity() : Entity() {

}

PhysicsEntity::PhysicsEntity(Rect _rect) : Entity(_rect) {
	
}

void PhysicsEntity::update(float dt) {
	// Update velocity and position
	velocity += acceleration * dt;

	// Want this: rect.position += velocity * dt;
	// But need to do collision stuff: (YES, y first)
	// TODO: check/confirm why this works best?/if this is even the best?
	rect.position.y += velocity.y * dt;

	// collision stuff

	rect.position.x += velocity.x * dt;

	// more collision stuff

	update_last_direction();
}

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