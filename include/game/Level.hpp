#pragma once

#include "File.hpp"
#include "GraphicsObjects.hpp"

#include "Constants.hpp"

class Level {
public:
	Level();
	Level(Framework::GraphicsObjects* _graphics_objects_ptr, std::string filepath); // Or maybe int for level number? Auto gen filepath from that?

	void update(float dt);
	void render();

private:
	void render_layer(std::string layer_name);

	Framework::GraphicsObjects* graphics_objects_ptr;

	Framework::TMXHandler::TMX tmx_data;
};