#pragma once

#include <memory>

#include "Maths.hpp"
#include "Physics.hpp"

#include "Animation.hpp"

using Framework::vec2;
using Framework::Rect;

// An entity is a game object which can be rendered, and can detect collisions with other entities.

class Entity {
public:
	Entity();
	Entity(Rect _rect, std::unique_ptr<AnimationInterface> _animation_ptr);

	void update(float dt);
	void render() const;

	bool colliding(const Entity& entity) const;

	Rect get_rect() const;

protected:
	Rect rect;

private:
	std::unique_ptr<AnimationInterface> animation_ptr;
};