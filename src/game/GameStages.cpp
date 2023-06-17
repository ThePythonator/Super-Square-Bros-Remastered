#include "GameStages.hpp"

void LevelSelectStage::start() {
	level = Level(graphics_objects, PATHS::LEVELS::LEVEL_SELECT);

	// TODO: Remove, just for testing!
	player = PlayerTest(graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]);
}

bool LevelSelectStage::update(float dt) {
	//level.update(dt);
	// Note: Level is used just for rendering/managing level? There should be a way to handle collisions which
	// the player/enemies can encounter, but should player management be separate?


	// TODO: Remove, just for testing!
	player.update(dt);

	return true;
}

void LevelSelectStage::render() {
	level.render();

	// TODO: Remove, just for testing!
	player.render();
}