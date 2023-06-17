#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"
#include "MenuStages.hpp"

#include "Level.hpp"

#include "Player.hpp" // TODO: Just for testing!

class LevelSelectStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Level level;

	// TODO: Remove! JUST FOR TESTING:
	PlayerTest player;
};

class GameStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();
};