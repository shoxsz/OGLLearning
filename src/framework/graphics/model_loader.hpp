#ifndef _MODEL_LOADER_HPP_
#define _MODEL_LOADER_HPP_

#include "vertices.hpp"

#include <string>
#include <fstream>

#include <utils/matrix.hpp>

struct ModelFace {
	Matrix<3, 3> attribs;
	bool hasTexture;
	bool hasNormals;
};

class Model {
public:
	unsigned int size()const { return sizeof(float)*(coords.countVertices() + normals.countVertices() + texCoords.countVertices()); }

	void clear() {
		coords.clear();
		normals.clear();
		texCoords.clear();
	}

	Vertices<Vertex>& getCoords() { return coords; }
	Vertices<Vertex>& getNormals() { return normals; }
	Vertices<TexturedVertex>& getTexCoords() { return texCoords; }
	std::vector<ModelFace>& getFaces() { return faces; }

private:
	Vertices<Vertex> coords;
	Vertices<Vertex> normals;
	Vertices<TexturedVertex> texCoords;
	std::vector<ModelFace> faces;
};

class ModelLoader {
public:
	void load(const std::string& file, Model& model);
private:

	void loadVertices(std::ifstream& file, std::vector<std::string>& line);
	void loadNormals(std::ifstream& file, std::vector<std::string>& line);
	void loadTextures(std::ifstream& file, std::vector<std::string>& line);
	void loadFaces(std::ifstream& file, std::vector<std::string>& line);

	Model* model;
};

#endif