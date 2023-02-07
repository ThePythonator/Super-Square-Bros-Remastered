#pragma once

#include "File.hpp"

#include "Constants.hpp"

class Level {
public:
	Level(std::string filepath); // Or maybe int for level number? Auto gen filepath from that?

	void update(float dt);
	void render();

private:
	Framework::TMXHandler::TMX tmx_data;
};