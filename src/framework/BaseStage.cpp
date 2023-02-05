#include "BaseStage.hpp"

namespace Framework {
	BaseStage::BaseStage() {

	}
	BaseStage::~BaseStage() {

	}

	void BaseStage::start() {

	}
	void BaseStage::end() {

	}

	BaseStage* BaseStage::next() {
		return _next;
	}

	bool BaseStage::finished() {
		return _finished;
	}

	bool BaseStage::delete_me() {
		return _delete_me;
	}

	void BaseStage::finish(BaseStage* next, bool can_delete_me) {
		_finished = true;
		_delete_me = can_delete_me;
		_next = next;
	}

	void BaseStage::init(GraphicsObjects* _graphics_objects, InputHandler* _input) {
		graphics_objects = _graphics_objects;
		input = _input;

		// We need to reset these in case we're reusing a stage
		buttons.clear();

		_finished = false;
		_delete_me = false;
		_next = nullptr;

		// Let user do any setup they need, possibly with graphics_objects or input
		start();
	}

	void BaseStage::set_transition(BaseTransition* _transition) {
		transition = _transition;
	}

	void BaseStage::clear_transition() {
		if (transition != nullptr) {
			delete transition;
			transition = nullptr;
		}
	}
}