#pragma once

#include "SDL.h"

#include "Maths.hpp"

namespace Framework {
	namespace MouseHandler {
		enum class MouseButtonState {
			STILL_UP, // Button isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Button has just been released
			STILL_DOWN, // Button is pressed (has already been down for at least one frame)
			JUST_PRESSED // Button has been pressed that frame
		};

		enum class MouseButton {
			LEFT,
			MIDDLE,
			RIGHT
		};

		struct MouseButtons {
			MouseButtonState LEFT, MIDDLE, RIGHT;
		};

		const uint8_t BUTTON_COUNT = sizeof(MouseButtons) / sizeof(MouseButtonState);

		union MouseButtonUnion {
			MouseButtons buttons;
			MouseButtonState button_array[BUTTON_COUNT];
		};

		class Mouse {
		public:
			Mouse();

			vec2 position();
			MouseButtonState button_state(MouseButton button);
			bool pressed(MouseButton button = MouseButton::LEFT);

			void update();
			void update_mouse(const SDL_Event& sdl_event);

			void set_cursor(bool visible);

			vec2 distance_moved();
			vec2 distance_dragged(MouseButton button = MouseButton::LEFT);

			// Horizontal scrolling is ignored.
			float scroll_amount();

		private:
			vec2 _position, _distance_moved;
			float _scroll_amount = 0.0f; // TODO: This maybe should be an int?

			MouseButtonUnion _buttons;
		};
	}
}