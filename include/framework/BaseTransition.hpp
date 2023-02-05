#pragma once

#include "Graphics.hpp"
#include "Timer.hpp"

namespace Framework {
	class BaseTransition {
	public:
		enum class TransitionState {
			OPENING,
			OPEN,
			CLOSING,
			CLOSED
		};

		BaseTransition();
		BaseTransition(Graphics* graphics);
		virtual ~BaseTransition();

		virtual void update(float dt) = 0;
		virtual void render() = 0;

		// Return the percentage completion of the current transition (from 0 to 1)
		virtual float percent() = 0;

		void open();
		void close();

		void set_open();
		void set_closed();

		bool is_open();
		bool is_closed();

		TransitionState state();


	protected:
		Graphics* _graphics = nullptr;

		TransitionState _state = TransitionState::OPEN;
		Timer _timer;
	};
}