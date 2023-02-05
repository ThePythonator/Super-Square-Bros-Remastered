#pragma once

#include <filesystem>

// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace Framework {
	std::string get_directory_path(std::string filepath);

	namespace JSONHandler {
		using namespace nlohmann;
		using namespace nlohmann::detail;

		// Reads and returns a json object from the file specified.
		// If the file was not found, returns an empty json object.
		json read(std::string filepath);
		// Writes a json object to the file specified
		void write(std::string filepath, json data, bool pretty_print = false);
	}
}