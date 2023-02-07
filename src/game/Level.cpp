#include "Level.hpp"

Level::Level(const Framework::Spritesheet& _spritesheet, std::string filepath) : spritesheet(_spritesheet) {
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

void Level::render_layer(const Framework::TMXHandler::TMXLayer& layer) {
	uint16_t x = 0;
	uint16_t y = 0;
	for (uint16_t index : layer) {
		spritesheet.sprite(index, Framework::Vec(x,y));
		x++;
		if (x == tmx_data.width) {
			x = 0;
			y++;
		}
	}
}