#include "Graphics.hpp"

namespace Framework {
	Graphics::Graphics() {

	}

	void Graphics::fill(const Colour& colour) {
		set_colour(colour);

		// NULL means draw rect over whole renderer
		SDL_RenderFillRect(renderer, NULL);
	}

	void Graphics::fill(const Colour& colour, uint8_t alpha) {
		fill(Colour(colour, alpha));
	}

	void Graphics::fill(const Rect& rect, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderFillRect(renderer, rect); // Maybe can use the overloaded version with a colour parameter?
	}

	void Graphics::fill(const Rect& rect, const Colour& colour, uint8_t alpha) {
		fill(rect, Colour(colour, alpha));
	}

	void Graphics::render_line(const vec2& start, const vec2& end, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderDrawLine(renderer, start, end); // Maybe can use the overloaded version with a colour parameter?
	}

	void Graphics::render_poly(const std::vector<vec2> points, const Colour& colour) {
		render_poly(points, VEC_NULL, colour);
	}

	void Graphics::render_poly(const std::vector<vec2> points, const vec2& offset, const Colour& colour) {
		set_colour(colour);

		for (uint16_t i = 0; i < points.size(); i++) {
			// Get next index (for end point)
			uint8_t next_i = i + 1 < points.size() ? i + 1 : 0;

			// Avoid unnecessary function calls and set_colour calls by using SDL_RenderDrawLine directly
			SDLUtils::SDL_RenderDrawLine(renderer, points[i] + offset, points[next_i] + offset);
		}
	}

	void Graphics::render_rect(const Rect& rect, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderDrawRect(renderer, rect);
	}

	void Graphics::render_filled_rect(const Rect& rect, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderFillRect(renderer, rect);
	}

	void Graphics::render_circle(const vec2& centre, float radius, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderDrawCircle(renderer, static_cast<int>(centre.x), static_cast<int>(centre.y), static_cast<int>(radius));
	}

	void Graphics::set_renderer(SDL_Renderer* _renderer) {
		renderer = _renderer;
	}

	SDL_Renderer* Graphics::get_renderer() {
		return renderer;
	}

	void Graphics::set_colour(const Colour& colour) {
		SDLUtils::SDL_SetRenderDrawColor(renderer, colour);
	}
}