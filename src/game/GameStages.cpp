#include "GameStages.hpp"

void LevelSelectStage::start() {
	level = Level(graphics_objects, PATHS::LEVELS::LEVEL_SELECT);
}

bool LevelSelectStage::update(float dt) {
	//level.update(dt);
	return true;
}

void LevelSelectStage::render() {
	level.render();
}