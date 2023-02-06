#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"
#include "MenuStages.hpp"

#include "Level.hpp"

class LevelSelectStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();

private:
	Level level;
};

class GameStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();
};