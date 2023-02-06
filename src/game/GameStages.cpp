#include "GameStages.hpp"

bool LevelSelectStage::update(float dt) {
	return false;
}

void LevelSelectStage::render() {
	level.render();
}