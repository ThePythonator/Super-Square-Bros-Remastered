#include "Entity.hpp"

Entity::Entity() {

}

Entity::Entity(Rect _rect) {
	rect = _rect;
}

bool Entity::colliding(const Entity& entity) const {
	return Physics::intersecting(rect, entity.get_rect());
}

Rect Entity::get_rect() const {
	return rect;
}