#pragma once

#include <utility>
#include <vector>
#include <map>

#include "Maths.hpp"
#include "Spritesheet.hpp"

struct AnimationFrame {
	uint16_t index;
	float duration;
	Framework::SpriteTransform transform;
};

// Multiple frames make an animation
typedef std::vector<AnimationFrame> Animation;

// Basic interface class
class AnimationInterface {
public:
	virtual void update(float dt) = 0;
	virtual void render(Framework::vec2 position) = 0;
};

class AnimationHandler : public AnimationInterface {
public:
	AnimationHandler(const Framework::Spritesheet& _spritesheet, Animation _animation, float time_offset = 0.0f, Framework::vec2 _position_offset = Framework::VEC_NULL);

	void update(float dt);
	void render(Framework::vec2 position);

private:
	const Framework::Spritesheet& spritesheet;
	Animation animation;
	Framework::vec2 position_offset;

	float current_time = 0.0f;
	
	uint16_t current_index = 0;
};

typedef std::map<Framework::vec2, Animation> MultiTileAnimation;

class MultiTileAnimationHandler : public AnimationInterface {
public:
	MultiTileAnimationHandler(const Framework::Spritesheet& _spritesheet, MultiTileAnimation _animation, float time_offset = 0.0f, Framework::vec2 _position_offset = Framework::VEC_NULL);

	void update(float dt);
	void render(Framework::vec2 position);

private:
	std::vector<AnimationHandler> animations;
};