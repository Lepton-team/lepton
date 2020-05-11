#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace WLep {
	class WLep_header {
	private:
		static const unsigned int max_version_length = 10;
		const std::string version_prefix = "WLep_v";

		std::streampos file_size(std::ifstream &file);
		std::vector<unsigned char> create_thumbnail_data(std::ifstream &thumbnail);

	public:
		WLep_header(const std::string const &version, std::string const &thumbnail_filename);

		std::string version;
		std::vector<unsigned char> data;
	};
};