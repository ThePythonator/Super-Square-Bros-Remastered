#include "Font.hpp"

namespace Framework {
	const uint8_t FONT_SHEET_WIDTH = 32;
	const uint8_t FONT_SHEET_HEIGHT = 3;
	const uint8_t ALPHABET_LENGTH = FONT_SHEET_WIDTH * FONT_SHEET_HEIGHT;

	const uint8_t ALPHABET_INDEX_START = 32;

	const uint8_t CHAR_DELETE = 127;
	const uint8_t CHAR_SPACE = ' '; // equivalent to 32

	// Font

	Font::Font() {

	}
	Font::Font(Spritesheet* spritesheet, uint8_t spacing) {
		font_spritesheet_ptr = spritesheet;
		_spacing = spacing;

		SDL_Surface* font_sheet_surface = font_spritesheet_ptr->get_image()->get_surface();
		uint8_t sprite_size = font_spritesheet_ptr->get_sprite_size();

		uint16_t base_x, base_y, x, y, left, right;
		Colour c;
		bool found;

		// Generate character_rects
		for (uint8_t i = 0; i < ALPHABET_LENGTH; i++) {
			base_x = (i % FONT_SHEET_WIDTH) * sprite_size;
			base_y = (i / FONT_SHEET_WIDTH) * sprite_size;

			left = 0;
			right = sprite_size - 1;

			// Find leftmost pixel
			found = false;

			x = y = 0;
			while (!found) {
				// Get pixel at (x, y)
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, base_x + x, base_y + y);

				if (c.a) {
					// We found the left edge of the character!
					left = x;
					found = true;
				}

				y++;
				if (y == sprite_size) {
					if (x == sprite_size - 1) {
						// Character is blank
						found = true;
					}

					y = 0;
					x++;
				}
			}

			// Find rightmost pixel
			found = false;

			x = sprite_size - 1;
			y = 0;
			while (!found) {
				// Get pixel at (x, y)
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, base_x + x, base_y + y);

				if (c.a) {
					// We found the right edge of the character!
					right = x;
					found = true;
				}

				y++;
				if (y == sprite_size) {
					if (x == 0) {
						// Character is blank
						found = true;
					}

					y = 0;
					x--;
				}
			}

			character_rects[i] = Rect{ base_x + left, base_y, right - left + 1, sprite_size };
		}

		// White
		Colour WHITE{ 0xFF, 0xFF, 0xFF };

		// Set all pixels to white (with no transparency at all) if they are not completely transparent
		for (x = 0; x < FONT_SHEET_WIDTH * sprite_size; x++) {
			for (y = 0; y < FONT_SHEET_HEIGHT * sprite_size; y++) {
				c = SDLUtils::SDL_GetPixel(font_sheet_surface, x, y);

				if (c.a) {
					// Pixel isn't transparent!
					SDLUtils::SDL_SetPixel(font_sheet_surface, x, y, WHITE);
				}
			}
		}

		// Update the image, so it transfers the changes we made from the surface over to the texture
		// Refresh takes a flag which determines which attribute to copy the changes from
		font_spritesheet_ptr->get_image()->refresh(Image::Flags::SDL_SURFACE);
	}

	void Font::render_text(std::string text, vec2 position, Colour colour, AnchorPosition anchor_position) {
		render_text(text, position, colour, font_spritesheet_ptr->get_scale(), anchor_position);
	}

	void Font::render_text(std::string text, vec2 position, Colour colour, float scale, AnchorPosition anchor_position) {
		set_colour(colour);

		vec2 current_position = position / scale;
		vec2 size;

		size.y = font_spritesheet_ptr->get_sprite_size();

		for (uint8_t c : text) {
			// Get width of character
			size.x += character_rect(c).size.x + _spacing;
		}

		// We added one too many spaces in the loop:
		size.x -= _spacing;

		// Handle positioning
		// Horizontal
		if (anchor_position & AnchorPosition::RIGHT) {
			current_position.x -= size.x;
		}
		else if (anchor_position & AnchorPosition::CENTER_X) {
			current_position.x -= size.x / 2.0f;
		}
		// Vertical
		if (anchor_position & AnchorPosition::BOTTOM) {
			current_position.y -= size.y;
		}
		else if (anchor_position & AnchorPosition::CENTER_Y) {
			current_position.y -= size.y / 2.0f;
		}

		for (uint8_t c : text) {
			// Render character
			render_char(c, current_position, scale);

			// Update current_position.x by getting character width
			current_position.x += character_rect(c).size.x + _spacing;
		}
	}

	Rect Font::character_rect(uint8_t c) {
		return (valid_character(c) || c == CHAR_SPACE) ? character_rects[c - ALPHABET_INDEX_START] : Rect();
	}

	bool Font::valid_character(uint8_t c) {
		return c >= ALPHABET_INDEX_START && c < ALPHABET_INDEX_START + ALPHABET_LENGTH && c != CHAR_SPACE && c != CHAR_DELETE;
	}

	Spritesheet* Font::get_spritesheet_ptr() {
		return font_spritesheet_ptr;
	}

	void Font::render_char(uint8_t c, vec2 position, float scale) {
		// Check character is one we have an image/rect for (don't include spaces or delete key)
		if (valid_character(c)) {
			// Render character
			font_spritesheet_ptr->rect(character_rects[c - ALPHABET_INDEX_START], position, scale);
		}
	}

	void Font::set_colour(Colour colour) {
		SDLUtils::SDL_SetTextureColorMod(font_spritesheet_ptr->get_image()->get_texture(), colour);
	}

	// Text

	Text::Text() {

	}
	Text::Text(Font* font, std::string text, Colour colour, Font::AnchorPosition anchor_position) {
		_font_ptr = font;
		_text = text;
		_colour = colour;
		_anchor = anchor_position;
		_scale = _font_ptr->get_spritesheet_ptr()->get_scale();
	}
	Text::Text(Font* font, std::string text, Colour colour, float scale, Font::AnchorPosition anchor_position) {
		_font_ptr = font;
		_text = text;
		_colour = colour;
		_anchor = anchor_position;
		_scale = scale;
	}

	void Text::render(vec2 position) const {
		render(position, _colour, _anchor);
	}
	void Text::render(vec2 position, Colour colour) const {
		render(position, colour, _anchor);
	}
	void Text::render(vec2 position, Font::AnchorPosition anchor_position) const {
		render(position, _colour, anchor_position);
	}
	void Text::render(vec2 position, Colour colour, Font::AnchorPosition anchor_position) const {
		_font_ptr->render_text(_text, position, colour, _scale, anchor_position);
	}

	void Text::set_text(std::string text) {
		_text = text;
	}
	std::string Text::get_text() const {
		return _text;
	}


	// String manipulation functions

	std::string trim_precision(std::string string, uint8_t precision) {
		// Trim string to precision
		if (precision <= 0) {
			// Assume trimming all after decimal place
			return string.substr(0, string.find('.'));
		}
		else {
			return string.substr(0, string.find('.') + precision + 1);
		}
	}
	// Not sure if both of these functions are needed since they have identical definitions:
	std::string trim_precision(float num, uint8_t precision) {
		return trim_precision(std::to_string(num), precision);
	}
	std::string trim_precision(double num, uint8_t precision) {
		return trim_precision(std::to_string(num), precision);
	}

	std::string normalise_magnitude(double num, uint8_t precision, std::string suffix) {
		if (num >= 1e9) {
			num /= 1e9;
			suffix = "G" + suffix;
		}
		else if (num >= 1e6) {
			num /= 1e6;
			suffix = "M" + suffix;
		}
		else if (num >= 1e3) {
			num /= 1e3;
			suffix = "k" + suffix;
		}

		return trim_precision(num, precision) + suffix;
	}
}