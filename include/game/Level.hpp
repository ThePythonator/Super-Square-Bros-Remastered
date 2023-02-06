#pragma once

#include "File.hpp"

class Level {
public:
	Level();
	Level(std::string filepath); // Or maybe int for level number? Auto gen filepath from that?

	void update(float dt);
	void render();


};