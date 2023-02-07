#include "Level.hpp"

Level::Level() {
	graphics_objects_ptr = nullptr;
}

Level::Level(Framework::GraphicsObjects* _graphics_objects_ptr, std::string filepath) {
	graphics_objects_ptr = _graphics_objects_ptr;

	tmx_data = Framework::TMXHandler::read(PATHS::BASE_PATH + PATHS::LEVELS::LOCATION + filepath);
	Framework::TMXHandler::reindex_empty_tiles(tmx_data, SPRITES::INDEX::BLANK);

	// TODO: do stuff with tmx_data? - sort out sprite spawns (in which case we can remove those layers)

	// TODO: Do stuff with tmx_data.layers[STRINGS::LEVELS::LAYERS::ENTITY_SPAWNS]
	tmx_data.layers.erase(STRINGS::LEVELS::LAYERS::ENTITY_SPAWNS);

	// Considering how to store tiles:
	// Using an array gives much more efficient lookup (so faster collision detection etc), but could take up to ~250MB
	// Using individual structs for each tile might be ~35MB, but requires ~4k comparisons to check for collisions
}

void Level::update(float dt) {

}

void Level::render() {
	// TODO: Need to render background : could it be a gradient of blue up to black as you get higher up?
	// Temporary solution:
	graphics_objects_ptr->graphics_ptr->fill(COLOURS::BLUE);

	render_layer(STRINGS::LEVELS::LAYERS::FOREGROUND);
}

void Level::render_layer(std::string layer_name) {
	uint16_t x = 0;
	uint16_t y = 0;
	for (uint16_t index : tmx_data.layers[layer_name]) {
		// Check that the tile isn't blank, in order to avoid unnecessarily rendering transparent tiles
		if (index != SPRITES::INDEX::BLANK) {
			graphics_objects_ptr->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(index, Framework::Vec(x, y) * SPRITES::SIZE);
		}
		x++;
		if (x == tmx_data.width) {
			x = 0;
			y++;
		}
	}
}