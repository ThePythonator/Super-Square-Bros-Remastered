#include "Maths.hpp"

namespace Framework {
	const float PI = 3.14159265f;
	//const float EPSILON = 0.0001f; // todo: check if reasonable

	const vec2 VEC_NULL = vec2{ 0.0f, 0.0f };
	const vec2 VEC_ONES = vec2{ 1.0f, 1.0f };
	const Rect RECT_NULL = Rect(VEC_NULL, VEC_NULL);

	// Rect and collision detection

	Rect::Rect(vec2 _position, vec2 _size) {
		position = _position;
		size = _size;
	}

	Rect::Rect(vec2 _position, int _size) {
		position = _position;
		size = Vec(_size, _size);
	}

	Rect::Rect(float x, float y, float width, float height) {
		position = vec2{ x, y };
		size = vec2{ width, height };
	}

	Rect::Rect(int x, int y, int width, int height) {
		position = vec2{ static_cast<float>(x), static_cast<float>(y) };
		size = vec2{ static_cast<float>(width), static_cast<float>(height) };
	}

	vec2 Rect::centre() const {
		return position + size / 2;
	}

	vec2 Rect::topleft() const {
		return position;
	}
	vec2 Rect::topright() const {
		return Vec(position.x + size.x, position.y);
	}
	vec2 Rect::bottomleft() const {
		return Vec(position.x, position.y + size.y);
	}
	vec2 Rect::bottomright() const {
		return position + size;
	}

	bool colliding(Rect a, vec2 b) {
		return b.x >= a.position.x && b.x <= a.position.x + a.size.x &&
			   b.y >= a.position.y && b.y <= a.position.y + a.size.y;
	}
	bool colliding(Rect a, Rect b) {
		return b.position.x + b.size.x >= a.position.x && b.position.x <= a.position.x + a.size.x &&
			   b.position.y + b.size.y >= a.position.y && b.position.y <= a.position.y + a.size.y;
	}

	Rect centred_rect(vec2 centre, vec2 size) {
		return Rect(centre - size / 2, size);
	}
	Rect centred_rect(vec2 centre, float size) {
		return Rect(centre - size / 2, size);
	}
	Rect centred_rect(float centre_x, float centre_y, float width, float height) {
		return centred_rect({ centre_x, centre_y }, { width, height });
	}

	vec2 Vec(float x, float y) {
		return vec2{ x, y };
	}

	vec2 Vec(int x, int y) {
		return vec2{ static_cast<float>(x), static_cast<float>(y) };
	}

	// Maths utilities

	float length_squared(vec2 v) {
		return linalg::length2(v);
	}

	vec2 normalise(vec2 v) {
		return linalg::normalize(v);
	}

	float deg_to_rad(float degrees) {
		return PI * degrees / 180.0f;
	}
	float rad_to_deg(float radians) {
		return 180.0f * radians / PI;
	}

	mat22 rotation_matrix(float angle) {
		// Anticlockwise rotation
		float s = std::sin(angle);
		float c = std::cos(angle);
		return mat22{ {c, s}, {-s, c} };
	}

	vec2 perpendicular_acw(vec2 vector) {
		return vec2{ -vector.y, vector.x };
	}

	vec2 perpendicular_cw(vec2 vector) {
		return vec2{ vector.y, -vector.x };
	}

	float clamp(float x, float _min, float _max) {
		return std::min(_max, std::max(_min, x));
	}

	float randf() {
		return (rand() % 1001) / 1000.0f;
	}

	float randf(float min, float max) {
		return min + randf() * (max - min);
	}
}