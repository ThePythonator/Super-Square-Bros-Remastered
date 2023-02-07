#pragma once

#include "Input.hpp"
#include "GraphicsObjects.hpp"
#include "Button.hpp"
#include "BaseTransition.hpp"

namespace Framework {
	class BaseStage {
	public:
		BaseStage();
		virtual ~BaseStage();

		// Called when stage becomes the current stage
		virtual void start();
		// Called when stage stops being the current stage
		virtual void end();

		// Returns false if the application should close
		virtual bool update(float dt) = 0;
		virtual void render() = 0;

		BaseStage* next();

		bool finished();
		bool delete_me();

		// Called only once. Override and use instead of constructor if you need access to graphics_objects or input
		// If this is overriden, make sure to call this at the start of the deriving function
		virtual void init(GraphicsObjects* _graphics_objects, InputHandler* _input);

		void set_transition(BaseTransition* _transition);
		void clear_transition();

	protected:
		void finish(BaseStage* next, bool can_delete_me = true);

		std::vector<Framework::Button> buttons;
		uint8_t button_selected = BUTTON_NONE_SELECTED;

		GraphicsObjects* graphics_objects = nullptr;
		InputHandler* input = nullptr;

		BaseTransition* transition = nullptr;

	private:
		bool _finished = false;
		bool _delete_me = false;
		BaseStage* _next = nullptr;
	};
}