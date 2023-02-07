#include "GameStages.hpp"

LevelSelectStage::LevelSelectStage() : level(Level(PATHS::LEVELS::LEVEL_SELECT)) {
	// TODO: Maybe need a Spritesheet/graphics ptr/ref to send to level?
}

bool LevelSelectStage::update(float dt) {
	//level.update(dt);
	return false;
}

void LevelSelectStage::render() {
	level.render();
}