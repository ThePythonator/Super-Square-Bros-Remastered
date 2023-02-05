#pragma once

#include "BaseTransition.hpp"
#include "Curves.hpp"

namespace Framework {
	class FadeTransition : public BaseTransition {
	public:
		FadeTransition(Graphics* graphics, Colour colour, float fade_time, uint8_t max_alpha = 0xFF, uint8_t min_alpha = 0x00);

		void update(float dt);
		void render();

		// Only meaningful when OPENING/CLOSING
		float percent();

	private:
		uint8_t _min = 0x00;
		uint8_t _max = 0xFF;

		float _fade_time = 0.0f;

		Colour _colour;
	};
}