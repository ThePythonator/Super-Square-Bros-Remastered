#pragma once

#include "SDL.h"

#include <string>

namespace Framework {
	namespace URLHandler {
		// Attempts to open the specified url with the default browser
		void open_url(std::string url);
	}
}