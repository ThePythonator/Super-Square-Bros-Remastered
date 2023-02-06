#include "Spritesheet.hpp"

namespace Framework {

	Spritesheet::Spritesheet() {

	}

	Spritesheet::Spritesheet(Image* spritesheet_image, uint8_t sprite_size, uint8_t default_scale, bool scale_positions) {
		_spritesheet_image = spritesheet_image;

		_sprite_size = sprite_size;
		_default_scale = default_scale;

		// If this is set to false, only scale the size, not the actual coordinates
		_scale_positions = scale_positions;

		// Get width and height of spritesheet
		int w = 0;
		int h = 0;
		SDL_QueryTexture(_spritesheet_image->get_texture(), NULL, NULL, &w, &h);

		_w = static_cast<uint32_t>(w);
		_h = static_cast<uint32_t>(h);

		_rows = _h / _sprite_size;
		_columns = _w / _sprite_size;
	}

	void Spritesheet::sprite(uint16_t index, vec2 position, SpriteTransform transform) const {
		sprite(index, position.x, position.y, transform);
	}
	void Spritesheet::sprite(uint16_t index, float x, float y, SpriteTransform transform) const {
		sprite(index, x, y, static_cast<float>(_default_scale), transform);
	}

	void Spritesheet::sprite(uint16_t index, vec2 position, float scale, SpriteTransform transform) const {
		sprite(index, position.x, position.y, scale, transform);
	}
	void Spritesheet::sprite(uint16_t index, float x, float y, float scale, SpriteTransform transform) const {
		Rect src = Rect(_sprite_size * (index % _columns), _sprite_size * (index / _columns), _sprite_size, _sprite_size);
		rect(src, x, y, scale, transform);
	}

	void Spritesheet::sprite(uint16_t index, vec2 position, float scale, float angle, SpriteTransform transform) const {
		sprite(index, position.x, position.y, scale, angle, transform);
	}
	void Spritesheet::sprite(uint16_t index, float x, float y, float scale, float angle, SpriteTransform transform) const {
		Rect src = Rect(_sprite_size * (index % _columns), _sprite_size * (index / _columns), _sprite_size, _sprite_size);
		rect(src, x, y, scale, angle, scale * src.size / 2, transform); // tod fi? - note: no idea what this means?? maybe todo fix?
	}

	void Spritesheet::sprite(uint16_t index, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform) const {
		sprite(index, position.x, position.y, scale, angle, centre, transform);
	}
	void Spritesheet::sprite(uint16_t index, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform) const {
		Rect src = Rect(_sprite_size * (index % _columns), _sprite_size * (index / _columns), _sprite_size, _sprite_size);
		rect(src, x, y, scale, angle, centre, transform);
	}


	void Spritesheet::rect(Rect src, vec2 position, SpriteTransform transform) const {
		rect(src, position.x, position.y, transform);
	}
	void Spritesheet::rect(Rect src, float x, float y, SpriteTransform transform) const {
		rect(src, x, y, static_cast<float>(_default_scale), transform);
	}

	void Spritesheet::rect(Rect src, vec2 position, float scale, SpriteTransform transform) const {
		rect(src, position.x, position.y, scale, transform);
	}
	void Spritesheet::rect(Rect src, float x, float y, float scale, SpriteTransform transform) const {
		Rect dst = Rect(_scale_positions ? x * scale : x, _scale_positions ? y * scale : y, src.size.x * scale, src.size.y * scale);
		_spritesheet_image->render(src, dst, transform_to_angle(transform), dst.size / 2, transform_to_imageflip(transform)); // to fix?
	}

	void Spritesheet::rect(Rect src, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform) const {
		rect(src, position.x, position.y, scale, angle, centre, transform);
	}
	void Spritesheet::rect(Rect src, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform) const {
		Rect dst = Rect(_scale_positions ? x * scale : x, _scale_positions ? y * scale : y, src.size.x * scale, src.size.y * scale);
		_spritesheet_image->render(src, dst, angle + transform_to_angle(transform), centre, transform_to_imageflip(transform));
	}

	uint8_t Spritesheet::get_sprite_size() const {
		return _sprite_size;
	}

	uint8_t Spritesheet::get_scale() const {
		return _default_scale;
	}

	Image* Spritesheet::get_image() const {
		return _spritesheet_image;
	}

	//void Spritesheet::set_blend_mode(SDL_BlendMode blending)
	//{
	//	// Set blending type
	//	SDL_SetTextureBlendMode(spritesheet_texture, blending);
	//}

	//void Spritesheet::set_alpha(uint8_t alpha)
	//{
	//	// Set texture alpha
	//	SDL_SetTextureAlphaMod(spritesheet_texture, alpha);
	//}

	/*uint8_t Spritesheet::get_alpha() {
		uint8_t alpha;
		SDL_GetTextureAlphaMod(spritesheet_texture, &alpha);
		return alpha;
	}*/


	// BaseSprite

	BaseSprite::BaseSprite() {

	}

	// ImageSprite

	ImageSprite::ImageSprite() { }
	ImageSprite::ImageSprite(Image* image, float scale) : _image(image), _scale(scale) { }

	void ImageSprite::render(vec2 position) {
		_image->render(Rect(position, _image->get_size() * _scale));
	}

	Rect ImageSprite::bounding_rect(vec2 position) {
		return Rect(position, _image->get_size());
	}

	// SpritesheetSprite

	SpritesheetSprite::SpritesheetSprite() { }
	SpritesheetSprite::SpritesheetSprite(Spritesheet* spritesheet, uint16_t index, float scale) : _spritesheet(spritesheet), _index(index), _scale(scale), _use_index(true) { }
	SpritesheetSprite::SpritesheetSprite(Spritesheet* spritesheet, Rect rect, float scale) : _spritesheet(spritesheet), _rect(rect), _scale(scale), _use_index(false) { }

	void SpritesheetSprite::render(vec2 position) {
		if (_use_index) _spritesheet->sprite(_index, position, _scale);
		else			_spritesheet->rect(_rect, position, _scale);
	}

	Rect SpritesheetSprite::bounding_rect(vec2 position) {
		vec2 size = _use_index ? VEC_ONES * _spritesheet->get_sprite_size() : _rect.size;
		return Rect(position, size * _scale);
	}

	// LineSprite

	LineSprite::LineSprite() : _points{ } { }
	LineSprite::LineSprite(Graphics* graphics, const vec2& start, const vec2& end, const Colour& colour) : _graphics(graphics), _points{ start, end }, _colour(colour) { }
	LineSprite::LineSprite(Graphics* graphics, const Rect& rect, const Colour& colour) : _graphics(graphics), _points{ rect.topleft(), rect.topright(), rect.bottomright(), rect.bottomleft() }, _colour(colour) { }
	LineSprite::LineSprite(Graphics* graphics, const std::vector<vec2>& points, const Colour& colour) : _graphics(graphics), _points(points), _colour(colour) { }

	void LineSprite::render(vec2 position) {
		_graphics->render_poly(_points, position, _colour);
	}

	Rect LineSprite::bounding_rect(vec2 position) {
		if (_points.size() == 0) return RECT_NULL;

		float top = _points[0].y;
		float left = _points[0].x;

		float bottom = top;
		float right = left;

		for (uint8_t i = 1; i < _points.size(); i++) {
			// i starts at 1 because we've initialised our temporary variables using _points[0]
			top = std::min(top, _points[i].y);
			bottom = std::max(bottom, _points[i].y);

			left = std::min(left, _points[i].x);
			right = std::max(right, _points[i].x);
		}

		return Rect(top, left, bottom - top, right - left);
	}

	// CircleSprite

	CircleSprite::CircleSprite() { }
	CircleSprite::CircleSprite(Graphics* graphics, float radius, const Colour& colour) : _graphics(graphics), _radius(radius), _colour(colour) { }

	void CircleSprite::render(vec2 position) {
		_graphics->render_circle(position, _radius, _colour);
	}

	Rect CircleSprite::bounding_rect(vec2 position) {
		return Rect(position - _radius, _radius * 2 * VEC_ONES);
	}
}