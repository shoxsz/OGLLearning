#ifndef _DDS_LOADER_HPP_
#define _DDS_LOADER_HPP_

#include <graphics\texture.hpp>

#include <memory>
#include <vector>
#include <fstream>

class DDSLoader {
public:
	Texture2DPtr load(const std::string& file);
};

#endif