#pragma once

#include "Maths.hpp"
#include "Physics.hpp"

using Framework::vec2;
using Framework::Rect;

// An entity is a game object which can be rendered, and can detect collisions with other entities.

class Entity {
public:
	Entity();
	Entity(Rect _rect);

	virtual void update(float dt) = 0;
	virtual void render() const = 0;

	bool colliding(const Entity& entity) const;

	Rect get_rect() const;

	void set_position(const vec2& position);

protected:
	Rect rect;
};