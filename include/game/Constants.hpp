#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Colour.hpp"

#include "Maths.hpp"

namespace WINDOW {
	const Framework::vec2 SIZE = Framework::vec2{ 1024, 768 };
	const Framework::vec2 SIZE_HALF = SIZE / 2;

	const std::string TITLE = "Super Square Bros: Remastered";

	const float TARGET_FPS = 60.0f;
	const float TARGET_DT = 1.0f / TARGET_FPS;

	const float MAX_DT = 0.05f;
}

namespace STRINGS {

}

namespace PATHS {
	const uint8_t DEPTH = 4;

	// Set at runtime
	std::string BASE_PATH;

	namespace IMAGES {
		const std::string LOCATION = "assets/images/";

		const std::string MAIN_SPRITESHEET = "spritesheet.png";
		const std::string FONT_SPRITESHEET = "font.png";
	}

	namespace SAVE_DATA {
		
	}

	namespace LEVELS {
		const std::string LOCATION = "assets/levels/";

		const std::string LEVEL_SELECT = "level_select.tmj";
	}
}

namespace GRAPHICS_OBJECTS {
	// Putting an enum in its own namespace is a bit hacky, but allows automatic casting, without needing enum class and all the manual casting.
	namespace IMAGES {
		enum IMAGES {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,

			TOTAL_IMAGES
		};
	}

	namespace SPRITESHEETS {
		enum SPRITESHEETS {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,

			TOTAL_SPRITESHEETS
		};
	}

	namespace FONTS {
		enum FONTS {
			MAIN_FONT,

			TOTAL_FONTS
		};
	}

	namespace TRANSITIONS {
		enum TRANSITIONS {
			FADE_TRANSITION,
			TOTAL_TRANSITIONS
		};
	}
}

namespace FONTS {
	namespace SIZE {
		const uint8_t MAIN_FONT = 16;
	}

	namespace SCALE {
		const uint8_t MAIN_FONT = 4;
	}

	namespace SPACING {
		const uint8_t MAIN_FONT = 1;
	}
}

namespace COLOURS {
	const Framework::Colour BLACK{ 0x00, 0x00, 0x00 };
	const Framework::Colour WHITE{ 0xFF, 0xFF, 0xFF };
}

//namespace TIMINGS {
//
//}

namespace TRANSITIONS {
	const float FADE_TIME = 1.0f;
}

namespace SPRITES {
	const uint8_t SIZE = 16;
	const uint8_t SIZE_HALF = SIZE / 2;
	const uint8_t SCALE = 4;
	const uint8_t UI_SCALE = 4;

	namespace INDEX {
		const uint16_t BLANK = 0x3ff;
	}
}

//namespace CURVES {
//	namespace BEZIER {
//		
//	}
//}

namespace BUTTONS {
	// NONE = 255, but this is defined as BUTTON_NONE_SELECTED in Button.hpp

	namespace TITLE {
		enum TITLE {
			PLAY,
			SETTINGS,
			QUIT,

			TOTAL
		};
	}

	namespace PAUSED {
		enum PAUSED {
			RESUME,
			EXIT,

			TOTAL
		};
	}
}

//namespace GAME {
//	
//}