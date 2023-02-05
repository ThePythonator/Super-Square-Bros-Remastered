#include "FadeTransition.hpp"

namespace Framework {
	FadeTransition::FadeTransition(Graphics* graphics, Colour colour, float fade_time, uint8_t max_alpha, uint8_t min_alpha) : BaseTransition(graphics) {
		_colour = colour;

		_fade_time = fade_time;

		_min = min_alpha;
		_max = max_alpha;
	}

	void FadeTransition::update(float dt) {
		if (_state == TransitionState::OPENING || _state == TransitionState::CLOSING) {
			_timer.update(dt);

			if (_timer.time() > _fade_time) {
				_state = _state == TransitionState::OPENING ? TransitionState::OPEN : TransitionState::CLOSED;
			}
		}
	}

	void FadeTransition::render() {
		// Handle fading
		switch (_state) {
		case TransitionState::CLOSED:
			// Fill with solid colour
			_graphics->fill(_colour, _max);
			break;

		case TransitionState::CLOSING:
			// Fade out
			_graphics->fill(_colour, Framework::Curves::linear(_min, _max, percent()));
			break;

		case TransitionState::OPENING:
			// Fade in
			_graphics->fill(_colour, Framework::Curves::linear(_max, _min, percent()));
			break;

		default:
			break;
		}
	}

	float FadeTransition::percent() {
		return _timer.time() / _fade_time;
	}
}