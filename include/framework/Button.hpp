#pragma once

#include "Image.hpp"
#include "Font.hpp"
#include "Input.hpp"

namespace Framework {
	const uint8_t BUTTON_NONE_SELECTED = 255;

	class Button {
	public:
		enum class ButtonState {
			STILL_UP, // Button isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Button has just been released
			STILL_DOWN, // Button is pressed (has already been down for at least one frame)
			JUST_PRESSED // Button has been pressed that frame
		};

		struct ButtonImages {
			Image* unselected = nullptr;
			Image* hovered = nullptr;
			Image* selected = nullptr;
		};

		Button();
		Button(Rect rect, ButtonImages images, Text text, uint8_t id = 0);
		Button(Rect render_rect, Rect collider_rect, ButtonImages images, Text text, uint8_t id = 0);

		ButtonState state() const;

		// Pressed means 'just pressed' - i.e., clicked this frame
		bool pressed() const;
		// Down means 'held down' - i.e. might have been clicked this frame, or might not
		bool down() const;

		// Hovered means mouse is currently over the button
		bool hovered() const;

		void update(InputHandler* input);
		void render() const;

		void set_position(vec2 position);

		std::string get_text() const;
		void set_text(std::string text);

		uint8_t get_id() const;

		vec2 position() const;

		void reset_state();

	private:
		ButtonState _state = ButtonState::STILL_UP;
		bool _mouse_over = false;

		Rect _render_rect, _collider_rect;
		ButtonImages _images;
		Text _text;

		uint8_t _id = 0;
	};
}