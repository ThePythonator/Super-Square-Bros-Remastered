#pragma once

#include "SDLUtils.hpp"

#include "Colour.hpp"

namespace Framework {
	class Graphics {
	public:
		Graphics();

		void fill(const Colour& colour);
		void fill(const Colour& colour, uint8_t alpha);
		void fill(const Rect& rect, const Colour& colour);
		void fill(const Rect& rect, const Colour& colour, uint8_t alpha);

		void render_line(const vec2& start, const vec2& end, const Colour& colour);
		void render_poly(const std::vector<vec2> points, const Colour& colour);
		void render_poly(const std::vector<vec2> points, const vec2& offset, const Colour& colour);
		void render_rect(const Rect& rect, const Colour& colour);
		void render_filled_rect(const Rect& rect, const Colour& colour);
		void render_circle(const vec2& centre, float radius, const Colour& colour);

		void set_renderer(SDL_Renderer* _renderer);
		SDL_Renderer* get_renderer();

	private:
		void set_colour(const Colour& colour);

		SDL_Renderer* renderer = nullptr;
	};
}