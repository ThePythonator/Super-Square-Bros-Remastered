#include "GameStages.hpp"

void LevelSelectStage::start() {
	level = Level(graphics_objects, PATHS::LEVELS::LEVEL_SELECT);
}

bool LevelSelectStage::update(float dt) {
	//level.update(dt);
	// Note: Level is used just for rendering/managing level? There should be a way to handle collisions which
	// the player/enemies can encounter, but should player management be separate?
	return true;
}

void LevelSelectStage::render() {
	level.render();
}