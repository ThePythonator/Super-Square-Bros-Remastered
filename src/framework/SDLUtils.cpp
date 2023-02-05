#include "SDLUtils.hpp"

namespace Framework::SDLUtils {

	bool init_sdl(SDL_Window*& window, SDL_Renderer*& renderer, const std::string& title, const vec2& size) {
		// Initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize!\nSDL Error: %s\n", SDL_GetError());
			SDL_ClearError();
			return false;
		}

		// Initialise SDL_image
		int img_init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
		if ((IMG_Init(img_init_flags) & img_init_flags) != img_init_flags) {
			printf("SDL_IMG could not initialize!\nSDL_IMG Error: %s\n", IMG_GetError());
			IMG_SetError("");
			return false;
		}

		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			size.x,
			size.y,
			SDL_WINDOW_SHOWN // Not sure if this is needed: it could be 0 instead?
		);

		// Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		// Set renderer mode
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		// Set scaling so that fullscreen mode is actually the same logical resolution
		SDL_RenderSetLogicalSize(renderer, size.x, size.y);

		return renderer != nullptr && window != nullptr;
	}

	std::string find_base_directory(std::string test_file, uint8_t depth) {
		printf("Attempting to find base directory...\n");

		std::string base_path = SDL_GetBasePath();

		SDL_Surface* test_surface = IMG_Load(test_file.c_str());

		if (test_surface != NULL) {
			base_path = "";
		}

		uint8_t count = 0;
		while (test_surface == NULL && count < depth) {
			printf("Trying path: %s\n", (base_path + test_file).c_str());

			test_surface = IMG_Load((base_path + test_file).c_str());

			if (test_surface == NULL) {
				base_path += "../";
			}

			count++;
		}

		if (test_surface == NULL) {
			printf("Could not find base directory!\n");
			return "";
		}

		SDL_FreeSurface(test_surface);
		SDL_ClearError();

		std::string message = "Found base directory: " + base_path + "\n\n";

		printf("%s", message.c_str());

		return base_path;
	}

	void SDL_SetRenderDrawColor(SDL_Renderer* renderer, const Colour& colour) {
		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	}

	Colour SDL_GetRenderDrawColor(SDL_Renderer* renderer) {
		Colour c;
		SDL_GetRenderDrawColor(renderer, &c.r, &c.g, &c.b, &c.a);
		return c;
	}

	void SDL_SetTextureColorMod(SDL_Texture* texture, const Colour& colour) {
		SDL_SetTextureColorMod(texture, colour.r, colour.g, colour.b);
	}


	void SDL_UnsetRenderTarget(SDL_Renderer* renderer) {
		::SDL_SetRenderTarget(renderer, NULL);
	}


	// Uses the current colour set by SDL_SetRenderDrawColour
	void SDL_RenderFillRect(SDL_Renderer* renderer, const Rect& rect) {
		SDL_Rect sdl_rect = SDLUtils::get_sdl_rect(rect);
		SDL_RenderFillRect(renderer, &sdl_rect);
	}

	void SDL_RenderDrawRect(SDL_Renderer* renderer, const Rect& rect) {
		SDL_Rect sdl_rect = SDLUtils::get_sdl_rect(rect);
		SDL_RenderDrawRect(renderer, &sdl_rect);
	}

	void SDL_RenderDrawLine(SDL_Renderer* renderer, const vec2& start, const vec2& end) {
		SDL_RenderDrawLine(renderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
	}


	void SDL_SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		SDL_LockSurface(surface);
		((uint32_t*)surface->pixels)[y * surface->w + x] = SDL_MapRGBA(surface->format, r, g, b, a);
		SDL_UnlockSurface(surface);
	}

	void SDL_SetPixel(SDL_Surface* surface, int x, int y, const Colour& colour) {
		SDL_SetPixel(surface, x, y, colour.r, colour.g, colour.b, colour.a);
	}

	void SDL_GetPixel(SDL_Surface* surface, int x, int y, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) {
		SDL_LockSurface(surface);
		SDL_GetRGBA(((uint32_t*)surface->pixels)[y * surface->w + x], surface->format, r, g, b, a);
		SDL_UnlockSurface(surface);
	}

	Colour SDL_GetPixel(SDL_Surface* surface, int x, int y) {
		uint8_t r, g, b, a;
		SDL_GetPixel(surface, x, y, &r, &g, &b, &a);
		return Colour(r, g, b, a);
	}

	int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
		// From https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c

		int offset_x = 0;
		int offset_y = radius;
		int d = radius - 1;
		int status = 0;

		while (offset_y >= offset_x) {
			status += SDL_RenderDrawPoint(renderer, x + offset_x, y + offset_y);
			status += SDL_RenderDrawPoint(renderer, x + offset_y, y + offset_x);
			status += SDL_RenderDrawPoint(renderer, x - offset_x, y + offset_y);
			status += SDL_RenderDrawPoint(renderer, x - offset_y, y + offset_x);
			status += SDL_RenderDrawPoint(renderer, x + offset_x, y - offset_y);
			status += SDL_RenderDrawPoint(renderer, x + offset_y, y - offset_x);
			status += SDL_RenderDrawPoint(renderer, x - offset_x, y - offset_y);
			status += SDL_RenderDrawPoint(renderer, x - offset_y, y - offset_x);

			if (status < 0) {
				status = -1;
				break;
			}

			if (d >= 2 * offset_x) {
				d -= 2 * offset_x + 1;
				offset_x += 1;
			}
			else if (d < 2 * (radius - offset_y)) {
				d += 2 * offset_y - 1;
				offset_y -= 1;
			}
			else {
				d += 2 * (offset_y - offset_x - 1);
				offset_y -= 1;
				offset_x += 1;
			}
		}

		return status;
	}

	SDL_Rect get_sdl_rect(Rect rect) {
		SDL_Rect sdl_rect{ static_cast<int>(rect.position.x), static_cast<int>(rect.position.y), static_cast<int>(rect.size.x), static_cast<int>(rect.size.y) };
		return sdl_rect;
	}

	SDL_Point get_sdl_point(vec2 vec) {
		SDL_Point sdl_point{ static_cast<int>(vec.x), static_cast<int>(vec.y) };
		return sdl_point;
	}

	SDL_RendererFlip get_sdl_renderer_flip(ImageFlip flip) {
		uint8_t sdl_flip = SDL_FLIP_NONE;

		if (flip & ImageFlip::FLIP_HORIZONTAL) sdl_flip |= SDL_FLIP_HORIZONTAL;
		if (flip & ImageFlip::FLIP_VERTICAL) sdl_flip |= SDL_FLIP_HORIZONTAL;

		return static_cast<SDL_RendererFlip>(sdl_flip);
	}


	// Calculate the rectangular intersection of two Rect instances
	Rect rect_intersection(const Rect& a, const Rect& b) {
		// If no intersection, we can't clip
		if (!colliding(a, b)) return RECT_NULL;

		Rect result; // note: broken? - note: not sure what this comment means?

		result.position.x = std::max(a.position.x, b.position.x);
		result.position.y = std::max(a.position.y, b.position.y);

		result.size.x = std::min(a.position.x + a.size.x, b.position.x + b.size.x) - result.position.x;
		result.size.y = std::min(a.position.y + a.size.y, b.position.y + b.size.y) - result.position.y;

		return result;
	}
}