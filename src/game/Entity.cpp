#include "Entity.hpp"

Entity::Entity() {

}

// Haven't used unique_ptr before so this could blow up when I use it :/
Entity::Entity(Rect _rect, std::unique_ptr<AnimationInterface> _animation_ptr) : animation_ptr(std::move(_animation_ptr)) {
	rect = _rect;
}

void Entity::update(float dt) {
	animation_ptr->update(dt);
}

void Entity::render() const {
	animation_ptr->render(rect.position);
}

bool Entity::colliding(const Entity& entity) const {
	return Physics::intersecting(rect, entity.get_rect());
}

Rect Entity::get_rect() const {
	return rect;
}