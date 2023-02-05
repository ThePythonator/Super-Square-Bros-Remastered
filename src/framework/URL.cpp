#include "URL.hpp"

namespace Framework {
	namespace URLHandler {
		void open_url(std::string url) {
			SDL_OpenURL(url.c_str());
		}
	}
}