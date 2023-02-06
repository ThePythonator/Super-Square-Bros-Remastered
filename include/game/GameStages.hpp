#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"
#include "MenuStages.hpp"

class LevelSelectStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();
};

class GameStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();
};