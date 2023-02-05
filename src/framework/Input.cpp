#include "Input.hpp"

namespace Framework {
	InputHandler::InputHandler() {
		key_data.keys = { KeyHandler::KeyState::STILL_UP };
	}

	// Need to call this before handle_sdl_event
	void InputHandler::update() {
		KeyHandler::update(key_data);
		mouse.update();
	}

	void InputHandler::handle_sdl_event(const SDL_Event& sdl_event) {
		KeyHandler::update_key(key_data, sdl_event);
		mouse.update_mouse(sdl_event);
	}

	void InputHandler::set_key(KeyHandler::Key key, KeyHandler::KeyState key_state) {
		KeyHandler::set_key(key_data, key, key_state);
	}

	bool InputHandler::is_up(KeyHandler::Key key) {
		KeyHandler::KeyState key_state = key_data.key_array[static_cast<int>(key)];
		return key_state == KeyHandler::KeyState::STILL_UP || key_state == KeyHandler::KeyState::JUST_RELEASED;
	}
	bool InputHandler::is_down(KeyHandler::Key key) {
		KeyHandler::KeyState key_state = key_data.key_array[static_cast<int>(key)];
		return key_state == KeyHandler::KeyState::STILL_DOWN || key_state == KeyHandler::KeyState::JUST_PRESSED;
	}
	bool InputHandler::just_up(KeyHandler::Key key) {
		KeyHandler::KeyState key_state = key_data.key_array[static_cast<int>(key)];
		return key_state == KeyHandler::KeyState::JUST_RELEASED;
	}
	bool InputHandler::just_down(KeyHandler::Key key) {
		KeyHandler::KeyState key_state = key_data.key_array[static_cast<int>(key)];
		return key_state == KeyHandler::KeyState::JUST_PRESSED;
	}

	bool InputHandler::is_up(MouseHandler::MouseButton button) {
		return !mouse.pressed(button);
	}

	bool InputHandler::is_down(MouseHandler::MouseButton button) {
		return mouse.pressed(button);
	}

	bool InputHandler::just_up(MouseHandler::MouseButton button) {
		MouseHandler::MouseButtonState button_state = mouse.button_state(button);
		return button_state == MouseHandler::MouseButtonState::JUST_RELEASED;
	}

	bool InputHandler::just_down(MouseHandler::MouseButton button) {
		MouseHandler::MouseButtonState button_state = mouse.button_state(button);
		return button_state == MouseHandler::MouseButtonState::JUST_PRESSED;
	}

	MouseHandler::Mouse* InputHandler::get_mouse() {
		return &mouse;
	}
}