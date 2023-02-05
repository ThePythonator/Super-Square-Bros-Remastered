#pragma once

#include "Maths.hpp"

namespace Framework {
	namespace Curves {
		// Linear interpolation, where t is from 0 to 1
		int linear(int start, int end, float t);
		float linear(float start, float end, float t);
		vec2 linear(vec2 start, vec2 end, float t);

		// Bezier curve, where t is from 0 to 1
		vec2 bezier(std::vector<vec2> nodes, float t);
	}
}