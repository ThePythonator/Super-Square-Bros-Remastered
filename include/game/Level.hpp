#pragma once

#include "File.hpp"
#include "Spritesheet.hpp"

#include "Constants.hpp"

class Level {
public:
	Level(const Framework::Spritesheet& spritesheet, std::string filepath); // Or maybe int for level number? Auto gen filepath from that?

	void update(float dt);
	void render();

private:
	void render_layer(const Framework::TMXHandler::TMXLayer& layer);

	const Framework::Spritesheet& spritesheet;

	Framework::TMXHandler::TMX tmx_data;
};