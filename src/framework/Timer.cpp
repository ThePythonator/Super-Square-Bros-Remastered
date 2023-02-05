#include "Timer.hpp"

namespace Framework {
	Timer::Timer() {

	}

	Timer::Timer(float loop_time) {
		_loop_time = loop_time;
	}

	void Timer::update(float dt) {
		if (_running) {
			_timer += dt;
		}

		while (_timer >= _loop_time) {
			_timer -= _loop_time;
		}
	}

	float Timer::time() {
		return _timer;
	}

	bool Timer::running() {
		return _running;
	}

	void Timer::start() {
		_running = true;
	}

	void Timer::stop() {
		_running = false;
	}

	void Timer::reset() {
		_timer = 0.0f;
	}
}