#include "Physics.hpp"

namespace Physics {
	bool intersecting(const vec2& a, const Rect& b)	{
		return a.x > b.position.x && a.x < b.position.x + b.size.x &&
		       a.y > b.position.y && a.y < b.position.y + b.size.y;
	}
	bool intersecting(const Rect& a, const Rect& b) {
		return a.position.x + a.size.x > b.position.x && a.position.x < b.position.x + b.size.x &&
		       a.position.y + b.size.x > b.position.y && a.position.y < b.position.y + b.size.y;
	}
}