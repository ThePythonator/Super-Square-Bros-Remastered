#pragma once

#include "Keys.hpp"
#include "Mouse.hpp"

namespace Framework {
	class InputHandler {
	public:
		InputHandler();

		void update();

		void handle_sdl_event(const SDL_Event& sdl_event);

		void set_key(KeyHandler::Key key, KeyHandler::KeyState key_state);

		bool is_up(KeyHandler::Key key); // Returns true if STILL_UP or JUST_RELEASED
		bool is_down(KeyHandler::Key key); // Returns true if STILL_DOWN or JUST_PRESSED
		bool just_up(KeyHandler::Key key); // Returns true if JUST_RELEASED
		bool just_down(KeyHandler::Key key); // Returns true if JUST_PRESSED

		bool is_up(MouseHandler::MouseButton button); // Returns true if STILL_UP or JUST_RELEASED
		bool is_down(MouseHandler::MouseButton button); // Returns true if STILL_DOWN or JUST_PRESSED
		bool just_up(MouseHandler::MouseButton button); // Returns true if JUST_RELEASED
		bool just_down(MouseHandler::MouseButton button); // Returns true if JUST_PRESSED

		MouseHandler::Mouse* get_mouse();

	private:
		KeyHandler::KeyUnion key_data;

		MouseHandler::Mouse mouse;
	};
}