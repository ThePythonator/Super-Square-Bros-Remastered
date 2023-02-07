#include "Level.hpp"

Level::Level() {
	spritesheet_ptr = nullptr;
}

Level::Level(Framework::Spritesheet* _spritesheet_ptr, std::string filepath) {
	spritesheet_ptr = _spritesheet_ptr;

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
	render_layer(STRINGS::LEVELS::FOREGROUND);
}

void Level::render_layer(std::string layer_name) {
	uint16_t x = 0;
	uint16_t y = 0;
	for (uint16_t index : tmx_data.layers[layer_name]) {
		spritesheet_ptr->sprite(index, Framework::Vec(x,y) * SPRITES::SIZE);
		x++;
		if (x == tmx_data.width) {
			x = 0;
			y++;
		}
	}
}