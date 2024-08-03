#pragma once

#include <cmath>
#include <limits>
#include <vector>

#include "linalg.h"

namespace Framework {
	typedef linalg::aliases::float2 vec2;
	typedef linalg::aliases::float2x2 mat22;
	//typedef vec2 Vec;
	//typedef mat22 Mat;

	using linalg::mul;
	using linalg::length;
	using linalg::dot;
	using linalg::cross;
	using linalg::inverse;
	using linalg::identity;

	extern const float PI;
	// extern const float EPSILON;

	extern const vec2 VEC_NULL;
	extern const vec2 VEC_ONES;

	class Rect {
	public:
		Rect(vec2 _position = VEC_NULL, vec2 _size = VEC_NULL);
		Rect(vec2 _position, int _size);
		Rect(float x, float y, float width = 0.0f, float height = 0.0f);
		Rect(int x, int y, int width = 0, int height = 0);

		vec2 centre() const;

		vec2 topleft() const;
		vec2 topright() const;
		vec2 bottomleft() const;
		vec2 bottomright() const;

		vec2 position;
		vec2 size;
	};

	Rect operator*(const Rect& r, const float s);
	Rect operator*(const float s, const Rect& r);

	extern const Rect RECT_NULL;

	bool colliding(Rect a, vec2 b);
	bool colliding(Rect a, Rect b);

	vec2 Vec(float x, float y);
	vec2 Vec(int x, int y);

	float length_squared(vec2 v);
	vec2 normalise(vec2 v);

	enum ImageFlip {
		FLIP_NONE		= 0b00,
		FLIP_HORIZONTAL = 0b01,
		FLIP_VERTICAL	= 0b10,

		FLIP_BOTH		= FLIP_HORIZONTAL | FLIP_VERTICAL
	};

	// Convert to/from radians and degrees
	float deg_to_rad(float degrees);
	float rad_to_deg(float radians);

	// angle is in radians
	mat22 rotation_matrix(float angle);

	// Get vector perpendicular to supplied vector
	vec2 perpendicular_acw(vec2 vector);
	vec2 perpendicular_cw(vec2 vector);

	float clamp(float x, float _min, float _max);

	/*
	* Generates a random float between 0 and 1 inclusive.
	* Resolution is 0.001f.
	*/
	float randf();

	/*
	* Generates a random float between min and max inclusive.
	*/
	float randf(float min, float max);
}