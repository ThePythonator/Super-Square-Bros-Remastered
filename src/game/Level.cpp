#include "Level.hpp"

Level::Level(std::string filepath) {
	tmx_data = Framework::TMXHandler::read(PATHS::BASE_PATH + PATHS::LEVELS::LOCATION + filepath);
	Framework::TMXHandler::reindex_empty_tiles(tmx_data, SPRITES::INDEX::BLANK);

	// TODO: do stuff with tmx_data? - sort out sprite spawns (in which case we can remove those layers)

	// Considering how to store tiles:
	// Using an array gives much more efficient lookup (so faster collision detection etc), but could take up to ~250MB
	// Using individual structs for each tile might be ~35MB, but requires ~4k comparisons to check for collisions
}

void Level::update(float dt) {

}

void Level::render() {

}