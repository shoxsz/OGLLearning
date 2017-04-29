#ifndef _OBJ_LOADER_HPP_
#define _OBJ_LOADER_HPP_

#include "vertices.hpp"

#include <string>
#include <fstream>

#include "3d_model.hpp"

class OBJLoader {
public:
	void load(const std::string& file, ModelPtr& model);
private:

	void loadVertices(std::ifstream& file, std::vector<std::string>& line);
	void loadNormals(std::ifstream& file, std::vector<std::string>& line);
	void loadTextures(std::ifstream& file, std::vector<std::string>& line);
	void loadFaces(std::ifstream& file, std::vector<std::string>& line);

	ModelPtr model;
};

#endif