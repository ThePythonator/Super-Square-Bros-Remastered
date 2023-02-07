#include "File.hpp"

namespace PATHS {
	// Set at runtime
	std::string BASE_PATH = "";
}
namespace Framework {

	std::string get_directory_path(std::string filepath) {
		return filepath.substr(0, filepath.find_last_of("\\/"));
	}

	namespace JSONHandler {
		// Uses https://github.com/nlohmann/json

		json read(std::string filepath) {
			printf("Attempting to read from %s\n", filepath.c_str());

			// Read from file
			json data;
			try {
				std::ifstream file(filepath);
				file >> data;
			}
			catch (const parse_error& error) {
				printf("Couldn't read file! Error: %s\n", error.what());
			}
			return data;
		}

		void write(std::string filepath, json data, bool pretty_print) {
			if (std::filesystem::create_directories(get_directory_path(filepath))) {
				printf("Created necessary directories.\n");
			}

			// Write to the file
			std::ofstream file(filepath);

			if (pretty_print) file << std::setw(4);

			file << data << std::endl;

			printf("Written to %s\n", filepath.c_str());
		}
	}

	namespace TMXHandler {
		TMX read(std::string filepath, TMXFormat file_format) {
			// Auto-detect file format if needed
			if (file_format == TMXFormat::AUTO) file_format = get_format(filepath);

			TMX tmx_data;

			switch (file_format) {
			case TMXFormat::JSON:
			{
				JSONHandler::json json_data = JSONHandler::read(filepath);
				if (!json_data.empty()) {
					json_data.get_to(tmx_data);
				}
			}
				break;
			case TMXFormat::XML:
				printf("Tiled level file format unsupported (XML)!");
				break;
			case TMXFormat::CSV:
				printf("Tiled level file format unsupported (CSV)!");
				break;
			case TMXFormat::UNKNOWN:
			default:
				printf("Tiled level file format unknown!");
				break;
			}

			return tmx_data;
		}

		// Determines the Tiled level file format from the file name
		TMXFormat get_format(std::string filepath) {
			std::string extension = std::filesystem::path(filepath).extension().string();
			
			if		(extension == ".json" || extension == ".tmj")   return TMXFormat::JSON;
			else if (extension == ".xml" || extension == ".tmx")    return TMXFormat::XML;
			else if (extension == ".csv")                           return TMXFormat::CSV;
			else                                                    return TMXFormat::UNKNOWN;
		}

		// Changes the null tile index from 0 to the value specified, reducing all other indices by 1
		void reindex_empty_tiles(TMX& data, uint16_t new_empty_index) {
			for (auto& [name, layer] : data.layers) {
				for (uint16_t i = 0; i < layer.size(); i++) {
					// Update the index
					layer[i] = layer[i] ? layer[i] - 1 : new_empty_index;
				}
			}
		}

		// Converts the JSON layer array into a map which allows layer lookup by name
		std::map<std::string, TMXLayer> parse_layers(const JSONHandler::json& layers) {
			std::map<std::string, TMXLayer> parsed_layers;

			for (const JSONHandler::json& layer : layers) {
				parsed_layers[layer.at("name").get<std::string>()] = layer.at("data").get<TMXLayer>();
			}

			return parsed_layers;
		}


		// Conversion methods
		
		void from_json(const JSONHandler::json& json_data, TMX& data) {
			try {
				json_data.at("width").get_to(data.width);
				json_data.at("height").get_to(data.height);
				data.layers = parse_layers(json_data.at("layers"));
			}
			catch (const JSONHandler::out_of_range& error) {
				printf("Couldn't parse JSON to TMX! Error: %s\n", error.what());
			}
		}
	}
}