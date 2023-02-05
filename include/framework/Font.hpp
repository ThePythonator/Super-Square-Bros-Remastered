#pragma once

#include <string>

#include "Spritesheet.hpp"

namespace Framework {
	extern const uint8_t FONT_SHEET_WIDTH;
	extern const uint8_t FONT_SHEET_HEIGHT;
	extern const uint8_t ALPHABET_LENGTH;

	extern const uint8_t ALPHABET_INDEX_START;

	extern const uint8_t CHAR_DELETE;
	extern const uint8_t CHAR_SPACE;

	class Font {
	public:
		enum AnchorPosition {
			LEFT			= 0b001000,
			CENTER_X		= 0b010000,
			RIGHT			= 0b100000,

			TOP				= 0b000001,
			CENTER_Y		= 0b000010,
			BOTTOM			= 0b000100,

			TOP_RIGHT		= TOP | RIGHT,
			TOP_CENTER		= TOP | CENTER_X,
			TOP_LEFT		= TOP | LEFT,

			CENTER_RIGHT	= CENTER_Y | RIGHT,
			CENTER_CENTER	= CENTER_X | CENTER_Y,
			CENTER_LEFT		= CENTER_Y | LEFT,

			BOTTOM_RIGHT	= BOTTOM | RIGHT,
			BOTTOM_CENTER	= BOTTOM | CENTER_X,
			BOTTOM_LEFT		= BOTTOM | LEFT
		};

		Font();
		Font(Spritesheet* spritesheet, uint8_t spacing = 1);

		void render_text(std::string text, vec2 position, Colour colour, AnchorPosition anchor_position = AnchorPosition::CENTER_CENTER);
		void render_text(std::string text, vec2 position, Colour colour, float scale, AnchorPosition anchor_position = AnchorPosition::CENTER_CENTER);

		Rect character_rect(uint8_t c);
		bool valid_character(uint8_t c);

		Spritesheet* get_spritesheet_ptr();

	private:
		void render_char(uint8_t c, vec2 position, float scale);
		void set_colour(Colour colour);

		Graphics* graphics_ptr = nullptr;
		Spritesheet* font_spritesheet_ptr = nullptr;

		Rect character_rects[96]; // TODO: sort out issue with ALPHABET_LENGTH - where to define it??

		uint8_t _spacing = 1;
	};

	class Text {
	public:
		Text();
		Text(Font* font, std::string text, Colour colour, Font::AnchorPosition anchor_position = Font::AnchorPosition::CENTER_CENTER);
		Text(Font* font, std::string text, Colour colour, float scale, Font::AnchorPosition anchor_position = Font::AnchorPosition::CENTER_CENTER);

		void render(vec2 position) const;
		void render(vec2 position, Colour colour) const;
		void render(vec2 position, Font::AnchorPosition anchor_position) const;
		void render(vec2 position, Colour colour, Font::AnchorPosition anchor_position) const;
		
		void set_text(std::string text);
		std::string get_text() const;

	private:
		Font* _font_ptr = nullptr;
		std::string _text;
		Colour _colour;
		Font::AnchorPosition _anchor = Font::AnchorPosition::CENTER_CENTER;
		float _scale = 1.0f;
	};


	// String manipulation functions

	/*
	* Trims all characters which are more than 'precision' chars after a full stop/decimal place.
	*
	* Example usage:
	*		trim_precision(std::to_string(my_float), 3);
	*/
	std::string trim_precision(std::string string, uint8_t precision);

	/*
	* Overloaded version which automatically converts a float to a string before trimming.
	*/
	std::string trim_precision(float num, uint8_t precision);
	std::string trim_precision(double num, uint8_t precision);

	std::string normalise_magnitude(double num, uint8_t precision, std::string suffix);
}