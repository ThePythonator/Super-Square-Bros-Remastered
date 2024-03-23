#include "PhysicsHandler.hpp"

PhysicsHandler::PhysicsHandler() {

}

PhysicsHandler::PhysicsHandler(Framework::TMXHandler::TMX* _tmx_ptr) : tmx_ptr(_tmx_ptr) {
	
}

void PhysicsHandler::update(std::vector<PhysicsEntity*> entities, float dt) {
	// TODO check for any player-enemy collisions?
	// Maybe check for every possible collision? and stop any entity from intersecting any other?

	for (PhysicsEntity* entity : entities) {
		update_entity(entity, dt);
	}
}

void PhysicsHandler::update_entity(PhysicsEntity* entity, float dt) {
	// Get constants for this entity
	const GAME::PHYSICS::PhysicsEntityConstants constants = entity->get_constants();

	// Get the rect for this entity
	Framework::Rect rect = entity->get_rect();

	// Update velocity and position
	Framework::vec2 velocity = entity->get_velocity() + entity->get_acceleration() * dt;
	
	// Add gravity
	velocity.y += constants.GRAVITY_ACCELERATION * dt;
	
	// Limit falling speed
	velocity.y = std::max(velocity.y, constants.TERMINAL_VELOCITY);
	
	// Update y axis first
	rect.position.y += velocity.y * dt;

	std::cout << tmx_ptr->width << "," << tmx_ptr->height << std::endl; // TODO: Remove

	// Handle tile collisions
	for (const TileData& tile : get_colliding_tiles(rect)) {
		// TODO

		// Check if index is one we want to handle? Or assume because it's in the foreground?

		if (velocity.y >= 0.0f && false) { // && less than halfway through tile
			// Set bottom of entity to top of block
			// TODO
		}
		else if (velocity.y <= 0.0f && false) { // && less than halfway up through underside of tile
			// Set top of entity to bottom of block
			// TODO
		}

		velocity.y = 0.0f;
	}
		
	// Find four tiles which might be colliding with.
	// For tile in tiles:
	//     If colliding:
	//         If travelling_downwards AND less_than_halfway_through_tile:
	//             Set bottom_of_entity TO top_of_block
	//         Else if travelling_upwards AND less_than_halfway_through_tile:
	//             Set top_of_entity TO bottom_of_block
	//         Set y_velocity TO 0.0f
	
	// TODO: similar for x-axis.
	
	// Update x axis second
	rect.position.x += velocity.x * dt;
	
	// TODO more collision stuff, using tmx_ptr

	// Write back the velocity to the entity
	entity->set_velocity(velocity);
	
	entity->update_last_direction();
}

std::vector<PhysicsHandler::TileData> PhysicsHandler::get_colliding_tiles(Framework::Rect entity_rect) {
	// Container for returned objects
	std::vector<TileData> results;

	// Find scaled tile position corresponding to the entity position
	Framework::vec2 scaled_entity_position = entity_rect.position / SPRITES::SIZE;

	// Truncate to find top left tile (within the scaled coordinates)
	uint32_t start_tile_x = static_cast<uint32_t>(scaled_entity_position.x);
	uint32_t start_tile_y = static_cast<uint32_t>(scaled_entity_position.y);

	for (uint32_t y = 0; y < 2; y++) {
		for (uint32_t x = 0; x < 2; x++) {
			uint32_t tile_x = start_tile_x + x;
			uint32_t tile_y = start_tile_y + y;

			uint32_t index = tile_y * tmx_ptr->width + tile_x;

			uint16_t tile_id = tmx_ptr->layers[STRINGS::LEVELS::LAYERS::FOREGROUND][index];

			// Lookup bounding rect and check it is nonempty
			Framework::Rect tile_rect = GAME::PHYSICS::BOUNDING_BOXES[tile_id];

			if (tile_rect.size.x == 0 || tile_rect.size.y == 0) continue;

			// Scale the position back up (after being truncated) to get the position of the top left corner
			uint32_t true_tile_x = tile_x * SPRITES::SIZE;
			uint32_t true_tile_y = tile_y * SPRITES::SIZE;

			// Offset the bounding rect by the position of the tile within the level
			tile_rect.position.x += true_tile_x;
			tile_rect.position.y += true_tile_y;

			// Check if entity is colliding
			if (Physics::intersecting(entity_rect, tile_rect)) {
				results.push_back(TileData{ tile_rect, tile_id });
			}
		}
	}
	
	return results;
}
