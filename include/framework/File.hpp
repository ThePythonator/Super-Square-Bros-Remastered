#pragma once

// https://github.com/nlohmann/json
#include <nlohmann/json.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

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

	namespace TMXHandler {
		// Alternatively, we could use a struct which stored more of the layer data
		typedef std::vector<uint16_t> TMXLayer;

		struct TMX {
			uint16_t width = 0;
			uint16_t height = 0;

			std::map<std::string, TMXLayer> layers;

			// Other attributes:
			// tilewidth, tileheight, tiledversion, version, type, tilesets, renderorder,
			// orientation, nextlayerid, nextobjectid, infinite, compressionlevel
		};

		enum class TMXFormat {
			JSON,
			XML,
			CSV,

			AUTO,
			UNKNOWN
		};

		// Reads and returns a TMX object from the Tiled level file specified.
		// If the file was not found, returns a TMX object with the read_failed flag set.
		TMX read(std::string filepath, TMXFormat file_format = TMXFormat::AUTO);

		// Writes a TMX object to the file specified
		// This shouldn't ever be needed, so it isn't implemented
		//void write(std::string filepath, TMX data, TMXFormat file_format = TMXFormat::AUTO);

		// Determines the Tiled level file format from the file name
		TMXFormat get_format(std::string filepath);

		// Conversion methods
		//void to_json(JSONHandler::json& json_data, const TMX& data);
		void from_json(const JSONHandler::json& json_data, TMX& data);

		//void to_json(JSONHandler::json& json_data, const std::map<std::string, TMXLayer>& data);
		void from_json(const JSONHandler::json& json_data, std::map<std::string, TMXLayer>& data);
	}
}