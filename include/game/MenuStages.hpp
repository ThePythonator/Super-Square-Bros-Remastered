#pragma once

#include "BaseStage.hpp"
#include "Timer.hpp"

#include "Constants.hpp"
#include "GameStages.hpp"

class IntroStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer intro_timer;
};

class TitleStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();
};

//class PausedStage : public Framework::BaseStage {
//public:
//	PausedStage(BaseStage* background_stage);
//
//	bool update(float dt);
//	void render();
//
//private:
//	BaseStage* _background_stage;
//};