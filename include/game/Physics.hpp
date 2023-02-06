#pragma once

#include "Maths.hpp"

namespace Physics {
	using Framework::vec2;
	using Framework::Rect;

	bool intersecting(const vec2& a, const Rect& b);
	bool intersecting(const Rect& a, const Rect& b);
}