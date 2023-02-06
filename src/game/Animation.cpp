#include "Animation.hpp"

AnimationHandler::AnimationHandler(const Framework::Spritesheet& _spritesheet, Animation _animation, float time_offset, Framework::vec2 _position_offset) : spritesheet(_spritesheet) {
	animation = _animation;
	current_time = time_offset;
	position_offset = _position_offset;
}

void AnimationHandler::update(float dt) {
	current_time += dt;
	float t = animation.at(current_index).duration;
	while (current_time >= t) {
		current_time -= t;
		current_index++;
		current_index %= animation.size();
		t = animation.at(current_index).duration;
	}
}

void AnimationHandler::render(Framework::vec2 position) {
	const AnimationFrame& current_frame = animation.at(current_index);
	spritesheet.sprite(current_frame.index, position + position_offset, current_frame.transform);
}

MultiTileAnimationHandler::MultiTileAnimationHandler(const Framework::Spritesheet& _spritesheet, MultiTileAnimation _animation, float time_offset, Framework::vec2 _position_offset) {
	for (const auto& [position, animation] : _animation) {
		animations.push_back(AnimationHandler(_spritesheet, animation, time_offset, _position_offset));
	}
}

void MultiTileAnimationHandler::update(float dt) {
	for (AnimationHandler& animation_handler : animations) {
		animation_handler.update(dt);
	}
}

void MultiTileAnimationHandler::render(Framework::vec2 position) {
	for (AnimationHandler& animation_handler : animations) {
		animation_handler.render(position);
	}
}