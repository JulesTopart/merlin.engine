
#include "pch.h"
#include "merlin/utils/util.h"
#include "merlin/utils/voxelizer.h"

#include <random>

namespace Merlin {	

	FileType getFileType(const std::string& file_path) {
		std::string extension = getFileExtension(file_path);
		if (extension == "obj") {
			return FileType::OBJ;
		}
		else if (extension == "stl") {
			return FileType::STL;
		}
		else if (extension == "geom") {
			return FileType::GEOM;
		}
		else if (extension == "gltf") {
			return FileType::GLTF;
		}
		else if (extension == "png") {
			return FileType::PNG;
		}
		else if (extension == "jpg" || extension == "jpeg") {
			return FileType::JPG;
		}
		else if (extension == "hdr") {
			return FileType::HDR;
		}
		else {
			// Unknown file type
			return FileType::UNKNOWN;
		}
	}

	std::string get_uuid() {
		static std::random_device dev;
		static std::mt19937 rng(dev());

		std::uniform_int_distribution<int> dist(0, 15);

		const char* v = "0123456789abcdef";
		const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

		std::string res;
		for (int i = 0; i < 16; i++) {
			if (dash[i]) res += "-";
			res += v[dist(rng)];
			res += v[dist(rng)];
		}
		return res;
	}

	std::string getFileExtension(const std::string& filepath) {
		size_t pos = filepath.find_last_of(".");
		if (pos == std::string::npos) {
			// No extension found
			return "";
		}
		return filepath.substr(pos + 1);
	}

	std::string getFileName(const std::string& filepath)
	{
		// Find the last occurrence of the directory separator character
		std::size_t pos = filepath.find_last_of("\\/");

		// If the separator was not found, return the entire filepath
		if (pos == std::string::npos) {
			return filepath;
		}

		// Return the part of the filepath after the separator
		return filepath.substr(pos + 1);
	}

	std::string getFileFolder(const std::string& filepath){
		// Find the last occurrence of the directory separator character
		std::size_t pos = filepath.find_last_of("\\/");

		// If the separator was not found, return the entire filepath
		if (pos == std::string::npos) {
			return filepath;
		}

		// Return the part of the filepath of last folder
		return filepath.substr(0, pos+1);
	}


}