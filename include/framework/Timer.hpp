#pragma once

#include <cfloat>

namespace Framework {
	class Timer {
	public:
		Timer();
		Timer(float loop_time);

		void update(float dt);

		float time();

		bool running();

		void start();
		void stop();
		void reset();

	private:
		float _timer = 0.0f;
		float _loop_time = FLT_MAX;
		
		bool _running = false;
	};
}