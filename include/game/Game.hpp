#pragma once

#include "BaseGame.hpp"

#include "MenuStages.hpp"

#include "FadeTransition.hpp"

class Game : public Framework::BaseGame {
public:
	Game();

private:
	void start();
	void end();

	void load_data();
	void clear_data();
};