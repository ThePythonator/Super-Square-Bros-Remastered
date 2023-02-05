#include "Window.hpp"

namespace Framework {
	Window::Window() {

	}

	void Window::set_fullscreen_mode(FullscreenMode mode) {
		uint32_t flags = 0;

		if (mode == FullscreenMode::FULLSCREEN) {
			flags = SDL_WINDOW_FULLSCREEN;
		}
		else if (mode == FullscreenMode::FULLSCREEN_DESKTOP) {
			flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		SDL_SetWindowFullscreen(window, flags);
	}

	Window::FullscreenMode Window::get_fullscreen_mode() {
		uint32_t flags = SDL_GetWindowFlags(window);

		if (flags & SDL_WINDOW_FULLSCREEN) {
			return FullscreenMode::FULLSCREEN;
		}
		else if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
			return FullscreenMode::FULLSCREEN_DESKTOP;
		}
		else {
			return FullscreenMode::NONE;
		}
	}

	void Window::set_window(SDL_Window* _window) {
		window = _window;
	}

	SDL_Window* Window::get_window() {
		return window;
	}
}