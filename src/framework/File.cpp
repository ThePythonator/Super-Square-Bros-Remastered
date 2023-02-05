#include "File.hpp"

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
}