#ifndef _3D_MODEL_HPP_
#define _3D_MODEL_HPP_

#include <memory>

#include <graphics\vertices.hpp>
#include <utils\matrix.hpp>

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

typedef std::shared_ptr<Model> ModelPtr;

#endif