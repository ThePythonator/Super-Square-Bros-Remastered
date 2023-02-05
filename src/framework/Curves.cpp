#include "Curves.hpp"

namespace Framework {
	namespace Curves {
		int linear(int start, int end, float t) {
			return static_cast<int>(linear(static_cast<float>(start), static_cast<float>(end), t));
		}

		float linear(float start, float end, float t) {
			return start + t * (end - start);
		}

		vec2 linear(vec2 start, vec2 end, float t) {
			return start + t * (end - start);
		}

		vec2 bezier(std::vector<vec2> nodes, float t) {
			if (nodes.size() == 0) {
				// No control points, just default to (0,0)
				return VEC_NULL;
			}
			else if (nodes.size() == 1) {
				// Only one node so we return it (end of recursion)
				return nodes[0];
			}

			std::vector<vec2> new_nodes;

			for (uint8_t i = 0; i < nodes.size() - 1; i++) {
				new_nodes.push_back(linear(nodes[i], nodes[i + 1], t));
			}

			return bezier(new_nodes, t);
		}
	}
}