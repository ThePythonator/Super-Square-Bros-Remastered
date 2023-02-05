#include "BaseTransition.hpp"

namespace Framework {
	BaseTransition::BaseTransition() {

	}
	BaseTransition::BaseTransition(Graphics* graphics) {
		_graphics = graphics;
	}
	BaseTransition::~BaseTransition() {

	}

	bool BaseTransition::is_open() {
		return _state == TransitionState::OPEN;
	}
	bool BaseTransition::is_closed() {
		return _state == TransitionState::CLOSED;
	}

	BaseTransition::TransitionState BaseTransition::state() {
		return _state;
	}

	void BaseTransition::open() {
		_state = TransitionState::OPENING;
		_timer.reset();
		_timer.start();
	}

	void BaseTransition::close() {
		_state = TransitionState::CLOSING;
		_timer.reset();
		_timer.start();
	}

	void BaseTransition::set_open() {
		_state = TransitionState::OPEN;
	}

	void BaseTransition::set_closed() {
		_state = TransitionState::CLOSED;
	}
}