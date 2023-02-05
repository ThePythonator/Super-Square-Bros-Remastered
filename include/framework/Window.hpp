#pragma once

#include "SDLUtils.hpp"

namespace Framework {
	class Window {
	public:
		enum class FullscreenMode {
			NONE,

			FULLSCREEN,
			FULLSCREEN_DESKTOP
		};

		Window();

		void set_fullscreen_mode(FullscreenMode mode);
		FullscreenMode get_fullscreen_mode();

		void set_window(SDL_Window* _window);
		SDL_Window* get_window();

	private:
		SDL_Window* window = nullptr;
	};
}