#pragma once

#include <vector>

#include "Graphics.hpp"
#include "Window.hpp"

#include "Image.hpp"
#include "Spritesheet.hpp"
#include "Font.hpp"
#include "BaseTransition.hpp"
#include "Button.hpp"

namespace Framework {
	struct GraphicsObjects {
		Graphics* graphics_ptr = nullptr;
		Window* window_ptr = nullptr;

		std::vector<Image*> image_ptrs;
		std::vector<Spritesheet*> spritesheet_ptrs;
		std::vector<Font*> font_ptrs;
		std::vector<BaseTransition*> transition_ptrs;

		std::vector<Button::ButtonImages> button_image_groups;
	};
}