#pragma once

#include "Maths.hpp"
#include "File.hpp"

#include "Constants.hpp"

#include "PhysicsEntity.hpp"

class PhysicsHandler {
public:
	PhysicsHandler();
	PhysicsHandler(Framework::TMXHandler::TMX* _tmx_ptr);

	void update(std::vector<PhysicsEntity*> entities, float dt);
	void update_entity(PhysicsEntity* entity, float dt);

private:

	struct TileData {
		Framework::Rect rect;
		uint32_t id;
	};

	std::vector<TileData> get_colliding_tiles(Framework::Rect entity_rect);

	Framework::TMXHandler::TMX* tmx_ptr = nullptr;
};