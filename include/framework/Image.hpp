#pragma once

#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "Graphics.hpp"

namespace Framework {
	class Image {
	public:
		enum Flags : uint8_t {
			NONE = 0b00,

			SDL_TEXTURE = 0b01,
			SDL_SURFACE = 0b10,

			ALL = SDL_TEXTURE | SDL_SURFACE
		};

		Image(Graphics* graphics);
		~Image();

		bool load(SDL_Surface* _surface, uint8_t flags = Flags::ALL);
		bool load(SDL_Texture* _texture, uint8_t flags = Flags::SDL_TEXTURE);
		bool load(std::string path, uint8_t flags = Flags::ALL);
		bool load(const vec2 size, uint8_t flags = Flags::SDL_TEXTURE);
		void free();

		bool refresh(uint8_t source_flag);

		void render(Rect source_rect, Rect destination_rect, float angle, vec2 centre, ImageFlip flip = ImageFlip::FLIP_NONE);
		void render(Rect source_rect, Rect destination_rect, float angle, ImageFlip flip = ImageFlip::FLIP_NONE);
		void render(Rect source_rect, Rect destination_rect);
		void render(Rect destination_rect = RECT_NULL);

		void render_line(const vec2& start, const vec2& end, const Colour& colour);
		void render_poly(const std::vector<vec2> points, const Colour& colour);
		void render_poly(const std::vector<vec2> points, const vec2& offset, const Colour& colour);
		void render_rect(const Rect& rect, const Colour& colour);
		void render_circle(const vec2& centre, float radius, const Colour& colour);

		void fill(const Colour& colour);

		void set_alpha(uint8_t alpha);

		SDL_Texture* get_texture();
		SDL_Surface* get_surface();

		vec2 get_size();

		void set_render_target();
		void unset_render_target();

	private:
		void final_setup();

		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = nullptr;

		Graphics* graphics_ptr = nullptr;

		uint8_t types = Flags::NONE;

		uint32_t _w = 0;
		uint32_t _h = 0;
	};

	Image* create_image(Graphics* graphics, std::string path, uint8_t flags = Image::Flags::ALL);
	Image* create_image(Graphics* graphics, const vec2& size);
	Image* create_image(Graphics* graphics, const vec2& size, const Colour& colour, bool use_alpha = false);

	namespace SDLUtils {
		void SDL_SetRenderTarget(SDL_Renderer* renderer, Image* image);

		void SDL_RenderFillRectToImage(SDL_Renderer* renderer, Image* image, const Rect& rect);
		void SDL_RenderFillRectToImage(SDL_Renderer* renderer, Image* image, const Rect& rect, const Colour& colour);

		void SDL_RenderFillImageWithoutAlphaMod(SDL_Renderer* renderer, Image* image, const Colour& colour);
		void SDL_RenderFillImageWithAlphaMod(SDL_Renderer* renderer, Image* image, const Colour& colour);
	}
}