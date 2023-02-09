#include "Entity.hpp"

Entity::Entity() {

}

// Haven't used unique_ptr before so this could blow up when I use it :/
Entity::Entity(Rect _rect) {
	rect = _rect;
}

bool Entity::colliding(const Entity& entity) const {
	return Physics::intersecting(rect, entity.get_rect());
}

Rect Entity::get_rect() const {
	return rect;
}