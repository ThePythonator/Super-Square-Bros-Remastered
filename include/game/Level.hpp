#pragma once

#include "File.hpp"
#include "Spritesheet.hpp"

#include "Constants.hpp"

class Level {
public:
	Level();
	Level(Framework::Spritesheet* _spritesheet_ptr, std::string filepath); // Or maybe int for level number? Auto gen filepath from that?

	void update(float dt);
	void render();

private:
	void render_layer(std::string layer_name);

	Framework::Spritesheet* spritesheet_ptr;

	Framework::TMXHandler::TMX tmx_data;
};