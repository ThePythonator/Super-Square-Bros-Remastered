#pragma once

#include "SDL.h"

namespace Framework {
	namespace KeyHandler {
		enum class KeyState {
			STILL_UP, // Key isn't pressed (has already been up for at least one frame)
			JUST_RELEASED, // Key has just been released
			STILL_DOWN, // Key is pressed (has already been down for at least one frame)
			JUST_PRESSED // Key has been pressed that frame
		};

		// enum Key and struct Keys must all have the same fields in the same order!
		enum class Key {
			UP, DOWN, LEFT, RIGHT,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
			SPACE, RETURN, ESCAPE
		};

		struct Keys {
			KeyState UP, DOWN, LEFT, RIGHT,
				A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
				NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
				SPACE, RETURN, ESCAPE; //, SHIFT, TAB
		};

		const uint8_t KEY_COUNT = sizeof(Keys) / sizeof(KeyState);

		union KeyUnion {
			Keys keys;
			KeyState key_array[KEY_COUNT];
		};

		void update(KeyUnion& key_handler);

		void update_key(KeyUnion& key_handler, const SDL_Event& sdl_event);

		void set_key(KeyUnion& key_handler, Key key, KeyState key_state);
	}
}