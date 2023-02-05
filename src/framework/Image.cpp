#include "Image.hpp"

namespace Framework {
	Image::Image(Graphics* graphics) {
		graphics_ptr = graphics;
	}

	Image::~Image() {
		free();
	}

	bool Image::load(SDL_Surface* _surface, uint8_t flags) {
		if (_surface == NULL) {
			printf("Surface passed to load() is NULL!\n");
			return false;
		}

		// Get width and height
		_w = _surface->w;
		_h = _surface->h;

		// Create texture from image
		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(graphics_ptr->get_renderer(), _surface);

		if (temp_texture == NULL)
		{
			printf("Unable to create texture from surface!\nSDL Error: %s\n", SDL_GetError());
			SDL_ClearError();
			return false;
		}

		if (flags & Flags::SDL_SURFACE) {
			// We want to keep the surface
			surface = _surface;
			types |= Flags::SDL_SURFACE; // set bit
		}

		if (flags & Flags::SDL_TEXTURE) {
			// We want to keep the surface
			texture = temp_texture;
			types |= Flags::SDL_TEXTURE; // Set bit
		}
		else {
			// Free
			SDL_DestroyTexture(temp_texture);
		}

		final_setup();

		return true;
	}

	bool Image::load(SDL_Texture* _texture, uint8_t flags) {
		if (flags & Flags::SDL_SURFACE) {
			// Can't convert texture to surface
			printf("Unable to convert texture to surface. Try calling load() with flags set to SDL_TEXTURE");
			return false;
		}

		if (_texture == NULL) {
			printf("Texture passed to load() is NULL!\n");
			return false;
		}

		int w, h;

		// Get width and height
		SDL_QueryTexture(_texture, NULL, NULL, &w, &h);

		_w = w;
		_h = h;

		if (flags & Flags::SDL_TEXTURE) {
			// We want to keep the surface
			texture = _texture;
			types |= Flags::SDL_TEXTURE; // Set bit
		}

		final_setup();

		return true;
	}

	bool Image::load(std::string path, uint8_t flags) {
		// Load image at specified path
		SDL_Surface* temp_surface = IMG_Load(path.c_str());

		if (temp_surface == NULL)
		{
			printf("Unable to create surface from %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
			SDL_ClearError();
			return false;
		}

		bool success = load(temp_surface, flags);
		// final_setup() is called in load(), so we don't need to call it again

		// Free the surface if we didn't need it, or loading failed
		if ((flags & Flags::SDL_SURFACE) == 0 || !success) {
			// Free
			SDL_FreeSurface(temp_surface);
		}

		return success;
	}

	// Loads a blank image
	bool Image::load(const vec2 size, uint8_t flags) {
		if (flags & Flags::SDL_SURFACE) {
			printf("Creating blank surfaces is currently not supported. Try calling load() with flags set to SDL_TEXTURE");
			return false;
		}

		texture = SDL_CreateTexture(graphics_ptr->get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y);

		_w = size.x;
		_h = size.y;

		if (texture == NULL)
		{
			printf("Unable to create blank texture!\nSDL Error: %s\n", SDL_GetError());
			SDL_ClearError();
			return false;
		}

		types |= Flags::SDL_TEXTURE;

		final_setup();

		return true;
	}

	void Image::free() {
		// Free the images
		if (types & Flags::SDL_SURFACE) {
			SDL_FreeSurface(surface);
			types &= ~Flags::SDL_SURFACE; // Unset bit
		}
		if (types & Flags::SDL_TEXTURE) {
			SDL_DestroyTexture(texture);
			types &= ~Flags::SDL_TEXTURE; // Unset bit
		}
	}

	bool Image::refresh(uint8_t source_flag) {
		// Refresh and update texture/surface using either the image's texture or surface

		// Don't allow source_flag to have multiple sources
		if (source_flag == Flags::SDL_SURFACE) {
			// Update texture from surface
			// Check we actually have a surface stored
			if (types & Flags::SDL_SURFACE) {
				// Create texture from the stored surface
				SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(graphics_ptr->get_renderer(), surface);

				if (temp_texture == NULL) {
					printf("Unable to convert surface to texture!\nSDL Error: %s\n", SDL_GetError());
					return false;
				}
				else {
					texture = temp_texture;
					return true;
				}
			}
			else {
				// Don't have a surface available
				return false;
			}
		}
		else if (source_flag == Flags::SDL_TEXTURE) {
			// Updates surface from texture
			// Not supported by SDL
			printf("Unable to convert texture to surface!\n");
			return false;
		}
		else {
			// Multiple or no sources, or not supported
			return false;
		}

		/*// First check, source_flag > 0, then check it is an exact power of two
		// n & (n-1) returns 0 if n is an exact power of two, so we need to invert it
		if (source_flag && !(source_flag & (source_flag - 1))) {
			// todo
			return true;
		}
		else {
			return false;
		}*/
	}

	void Image::render(Rect source_rect, Rect destination_rect, float angle, vec2 centre, ImageFlip flip) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		SDL_Rect sdl_src_rect = SDLUtils::get_sdl_rect(source_rect);
		SDL_Rect sdl_dst_rect = SDLUtils::get_sdl_rect(destination_rect);

		SDL_Point sdl_centre = SDLUtils::get_sdl_point(centre);

		SDL_RenderCopyEx(graphics_ptr->get_renderer(), texture, &sdl_src_rect, &sdl_dst_rect, angle, &sdl_centre, SDLUtils::get_sdl_renderer_flip(flip));
	}

	void Image::render(Rect source_rect, Rect destination_rect, float angle, ImageFlip flip) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		render(source_rect, destination_rect, angle, destination_rect.size / 2, flip); // todo? - not sure what it was I needed to do...
	}

	void Image::render(Rect source_rect, Rect destination_rect) {
		// If size is unset, default to Image's size
		if (source_rect.size == vec2{ 0.0f, 0.0f })			source_rect.size = get_size();
		if (destination_rect.size == vec2{ 0.0f, 0.0f })	destination_rect.size = get_size();

		SDL_Rect sdl_src_rect = SDLUtils::get_sdl_rect(source_rect);
		SDL_Rect sdl_dst_rect = SDLUtils::get_sdl_rect(destination_rect);

		// Render from texture to screen
		SDL_RenderCopy(graphics_ptr->get_renderer(), texture, &sdl_src_rect, &sdl_dst_rect);
	}

	void Image::render(Rect destination_rect) {
		render(RECT_NULL, destination_rect);
	}


	void Image::render_line(const vec2& start, const vec2& end, const Colour& colour) {
		set_render_target();
		graphics_ptr->render_line(start, end, colour);
		unset_render_target();
	}

	void Image::render_poly(const std::vector<vec2> points, const Colour& colour) {
		set_render_target();
		graphics_ptr->render_poly(points, colour);
		unset_render_target();
	}

	void Image::render_poly(const std::vector<vec2> points, const vec2& offset, const Colour& colour) {
		set_render_target();
		graphics_ptr->render_poly(points, colour);
		unset_render_target();
	}

	void Image::render_rect(const Rect& rect, const Colour& colour) {
		set_render_target();
		graphics_ptr->render_rect(rect, colour);
		unset_render_target();
	}

	void Image::render_circle(const vec2& centre, float radius, const Colour& colour) {
		set_render_target();
		graphics_ptr->render_circle(centre, radius, colour);
		unset_render_target();
	}


	void Image::fill(const Colour& colour) {
		SDLUtils::SDL_RenderFillImageWithAlphaMod(graphics_ptr->get_renderer(), this, colour);
	}


	void Image::set_alpha(uint8_t alpha) {
		if (types & Flags::SDL_SURFACE) SDL_SetSurfaceAlphaMod(surface, alpha);
		if (types & Flags::SDL_TEXTURE) SDL_SetTextureAlphaMod(texture, alpha);
	}

	// Returns SDL_Texture* if loaded, otherwise returns nullptr
	SDL_Texture* Image::get_texture() {
		return texture;
	}

	// Returns SDL_Surface* if loaded, otherwise returns nullptr
	SDL_Surface* Image::get_surface() {
		return surface;
	}

	vec2 Image::get_size() {
		return vec2{ static_cast<float>(_w), static_cast<float>(_h)};
	}

	void Image::set_render_target() {
		SDLUtils::SDL_SetRenderTarget(graphics_ptr->get_renderer(), this);
	}
	void Image::unset_render_target() {
		SDLUtils::SDL_UnsetRenderTarget(graphics_ptr->get_renderer());
	}

	void Image::final_setup() {
		if (types & Flags::SDL_SURFACE) {
			SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
		}
		if (types & Flags::SDL_TEXTURE) {
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
	}


	Image* create_image(Graphics* graphics, std::string path, uint8_t flags) {
		Image* image_ptr = new Image(graphics);
		image_ptr->load(path, flags);
		return image_ptr;
	}
	Image* create_image(Graphics* graphics, const vec2& size) {
		Image* image_ptr = new Image(graphics);
		image_ptr->load(size);
		return image_ptr;
	}
	Image* create_image(Graphics* graphics, const vec2& size, const Colour& colour, bool use_alpha) {
		Image* image_ptr = create_image(graphics, size);
		// Fill image white first
		SDLUtils::SDL_RenderFillRectToImage(graphics->get_renderer(), image_ptr, Rect(VEC_NULL, size), Colour(0xFF, 0xFF, 0xFF));

		if (use_alpha) {
			SDLUtils::SDL_RenderFillImageWithAlphaMod(graphics->get_renderer(), image_ptr, colour);
		}
		else {
			SDLUtils::SDL_RenderFillImageWithoutAlphaMod(graphics->get_renderer(), image_ptr, colour);
		}

		return image_ptr;
	}


	namespace SDLUtils {
		void SDL_SetRenderTarget(SDL_Renderer* renderer, Image* image) {
			if (SDL_SetRenderTarget(renderer, image->get_texture())) {
				printf("Unable to set render target to texture!\nSDL Error: %s\n", SDL_GetError());
				SDL_ClearError();
			}
		}


		// Note: it appears that alpha is treated slightly weirdly.
		// The rect seems to be rendered with colour converted to an equivalent non-alpha colour, so when rendering it, the texture appears to have no alpha.
		// For example, black with 50% alpha may appear grey and non-transparent when the texture is rendered to the window.
		// Using SDL_RenderFillImageWithAlphaMod is recommended if you need to create a semi-transparent single-colour image
		void SDL_RenderFillRectToImage(SDL_Renderer* renderer, Image* image, const Rect& rect) {
			// Set image as render target, then unset once done
			SDLUtils::SDL_SetRenderTarget(renderer, image);
			//if (SDL_SetRenderTarget(renderer, image->get_texture())) printf("oops\n");

			SDL_RenderFillRect(renderer, rect);

			SDL_UnsetRenderTarget(renderer);
		}

		void SDL_RenderFillRectToImage(SDL_Renderer* renderer, Image* image, const Rect& rect, const Colour& colour) {
			// Keep old colour and set back afterwards
			Colour old_colour = SDL_GetRenderDrawColor(renderer);
			SDL_SetRenderDrawColor(renderer, colour);

			SDL_RenderFillRectToImage(renderer, image, rect);

			SDL_SetRenderDrawColor(renderer, old_colour);
		}

		void SDL_RenderFillImageWithoutAlphaMod(SDL_Renderer* renderer, Image* image, const Colour& colour) {
			// Render with no alpha
			SDL_RenderFillRectToImage(renderer, image, Rect(VEC_NULL, image->get_size()), Colour(colour, 0xFF));
		}

		void SDL_RenderFillImageWithAlphaMod(SDL_Renderer* renderer, Image* image, const Colour& colour) {
			// Render with no alpha
			SDL_RenderFillImageWithoutAlphaMod(renderer, image, colour);

			// Set alpha of texture to alpha rendered
			image->set_alpha(colour.a);
		}
	}
}