#include "WLep_header.hh"

typedef unsigned char uChar;

namespace VectorUtil {
	template <typename T, typename V>
	inline void append(T &t, std::vector<V> &vec) {
		vec.insert(vec.end(), std::begin(t), std::end(t));
	}

	template <typename T, typename V>
	inline void prepend(T &t, std::vector<V> &vec) {
		vec.insert(vec.begin(), std::begin(t), std::end(t));
	}
}

std::streampos WLep::WLep_header::file_size(std::ifstream &file) {
	file.seekg(0, file.beg);

	std::streampos size = file.tellg();
	file.seekg(0, file.end);
	size = file.tellg() - size;

	file.seekg(0, file.beg);

	return size;
}

std::vector<uChar> WLep::WLep_header::create_thumbnail_data(std::ifstream &thumbnail) {
	std::vector<uChar> res;

	uChar ch = thumbnail.get();
	while (thumbnail.good()) {
		res.push_back(ch);
		ch = thumbnail.get();
	}

	return res;
}

WLep::WLep_header::WLep_header(const std::string const &version, std::string const &thumbnail_filename) {
	std::string str_version = "";

	str_version = str_version.append(this->version_prefix)
		.append(version)
		.substr(0, this->max_version_length);

	const std::string str_version_length = std::to_string(str_version.length());
	str_version.insert(0, str_version_length);

	this->data = std::vector<uChar>();
	VectorUtil::append<std::string, uChar>(str_version, data);

	//TODO: Resize thumbnail
	std::ifstream thumbnail;
	thumbnail.open(thumbnail_filename, std::ios::binary | std::ios::in);

	std::streampos f_size = file_size(thumbnail);
	std::vector<uChar> thumbnail_data = create_thumbnail_data(thumbnail);

	thumbnail.close();

	VectorUtil::prepend<std::string, uChar>(std::to_string(f_size), thumbnail_data);
	VectorUtil::append<std::vector<uChar>, uChar>(thumbnail_data, data);
}