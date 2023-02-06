#pragma once

#include "Image.hpp"
#include "Transform.hpp"

namespace Framework {
	class Spritesheet {
	public:
		static const uint8_t DEFAULT_SPRITE_SIZE = 16;

		Spritesheet();
		Spritesheet(Image* spritesheet_image, uint8_t sprite_size = 16, uint8_t default_scale = 1, bool scale_positions = true);

		void sprite(uint16_t index, vec2 position, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, float x, float y, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, vec2 position, float scale, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, vec2 position, float scale, float angle, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, float x, float y, float scale, float angle, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE) const;
		void sprite(uint16_t index, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE) const;

		void rect(Rect src, vec2 position, SpriteTransform transform = SpriteTransform::NONE) const;
		void rect(Rect src, float x, float y, SpriteTransform transform = SpriteTransform::NONE) const;
		void rect(Rect src, vec2 position, float scale, SpriteTransform transform = SpriteTransform::NONE) const;
		void rect(Rect src, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE) const;
		void rect(Rect src, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE) const;
		void rect(Rect src, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE) const;

		uint8_t get_sprite_size() const;
		uint8_t get_scale() const;

		Image* get_image() const;

	private:
		Image* _spritesheet_image = nullptr;

		uint32_t _w = 0;
		uint32_t _h = 0;
		uint8_t _rows = 0;
		uint8_t _columns = 0;

		uint8_t _sprite_size = DEFAULT_SPRITE_SIZE;
		uint8_t _default_scale = 1;

		bool _scale_positions = false;
	};

	class BaseSprite {
	public:
		BaseSprite();

		virtual void render(vec2 position) = 0;

		virtual Rect bounding_rect(vec2 position) = 0;
	};

	class ImageSprite : public BaseSprite {
	public:
		ImageSprite();
		ImageSprite(Image* image, float scale = 1.0f);

		void render(vec2 position);

		Rect bounding_rect(vec2 position);

	private:
		Image* _image = nullptr;

		const float _scale = 1.0f;
	};

	class SpritesheetSprite : public BaseSprite {
	public:
		SpritesheetSprite();
		SpritesheetSprite(Spritesheet* spritesheet, uint16_t index, float scale = 1.0f);
		SpritesheetSprite(Spritesheet* spritesheet, Rect rect, float scale = 1.0f);

		void render(vec2 position);

		Rect bounding_rect(vec2 position);

	private:
		Spritesheet* _spritesheet = nullptr;

		const uint16_t _index = 0;
		const Rect _rect = Rect();
		const float _scale = 1.0f;

		const bool _use_index = false;
	};

	class LineSprite : public BaseSprite {
	public:
		LineSprite();
		LineSprite(Graphics* graphics, const vec2& start, const vec2& end, const Colour& colour);
		LineSprite(Graphics* graphics, const Rect& rect, const Colour& colour);
		LineSprite(Graphics* graphics, const std::vector<vec2>& points, const Colour& colour);

		void render(vec2 position);

		Rect bounding_rect(vec2 position);

	private:
		Graphics* _graphics = nullptr;

		const std::vector<vec2> _points;
		const Colour _colour;
	};

	class CircleSprite : public BaseSprite {
	public:
		CircleSprite();
		CircleSprite(Graphics* graphics, float radius, const Colour& colour);

		void render(vec2 position);

		Rect bounding_rect(vec2 position);

	private:
		Graphics* _graphics = nullptr;

		const float _radius = 1.0f;
		const Colour _colour;
	};
}