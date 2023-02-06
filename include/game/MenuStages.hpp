#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"
#include "GameStages.hpp"

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