#ifndef _VERTICES_HPP_
#define _VERTICES_HPP_

#include "buffer_object.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"
#include "enums.hpp"

#include <GL/glew.h>
#include <vector>

struct Vertex{
	enum{CoordCount = 3, GLType = GL_FLOAT};
	float x, y, z;
};

struct TexturedVertex{
	enum{CoordCount = 2, GLType = GL_FLOAT};
    float u, v;
};

struct ColoredVertex{
	enum{CoordCount = 4, GLType = GL_FLOAT};
    float r, g, b, a;
};

template<typename vertexType = Vertex, typename dataType = float>
class Vertices{
public:
	Vertices():mustUpdate(false), accessType(AccessType::Static){}
	Vertices(AccessType accessType):mustUpdate(false), accessType(accessType){}

	void addVertex(const vertexType& vertex);
	void addVertices(const std::initializer_list<vertexType>& vertices){
		for(const vertexType& vertex : vertices)
			addVertex(vertex);
	}
	void addIndice(unsigned int indice){
		indices.push_back(indice);
	}

	void setIndices(const unsigned int* indices, unsigned int n){
		this->indices.clear();
		this->indices.resize(n);
		for(unsigned int i = 0; i < n; i++){
			this->indices[i] = indices[i];
		}
	}

	void setIndices(const std::vector<unsigned int>& indices){
		this->indices = indices;
	}

	/*update the data into the vbo if needed
	return true if update was needed*/
	bool update(bool useIndices = false);

	/*feed the vertex attrib with the buffer current data*/
	void feed(unsigned int vertexAttrib);

	void clear(){
		vertexBuffer.dispose();
		indBuffer.dispose();
		coords.clear();
		indices.clear();
	}

	void setAccessType(AccessType accessType) {
		this->accessType = accessType;
	}

	AccessType getAccessType()const{ return accessType; }
	unsigned int countVertices()const{ return (coords.size() / vertexType::CoordCount); }
	const std::vector<unsigned int>& getIndices()const{ return indices; }
	const std::vector<float>& getCoords()const{ return coords; }

protected:
	AccessType accessType;

	bool mustUpdate;

	BufferObject vertexBuffer;
	BufferObject indBuffer;
	std::vector<dataType> coords;
	std::vector<unsigned int> indices;
};

template<typename vertexType, typename dataType>
void Vertices<vertexType, dataType>::addVertex(const vertexType& vertex){
	unsigned int oldSize = coords.size();
	coords.insert(coords.end(), vertexType::CoordCount, 0);
	//raw copy of the data
	memcpy(coords.data() + oldSize, &vertex, sizeof(vertexType));
	mustUpdate = true;
}

template<typename vertexType, typename dataType>
bool Vertices<vertexType, dataType>::update(bool useIndices){
	if(mustUpdate && coords.size() > 0){
		if(!vertexBuffer.isCreated())
			vertexBuffer.create(Array);

		vertexBuffer.bind();
		vertexBuffer.allocate((void*)coords.data(), coords.size() * sizeof(dataType), accessType);

		if(useIndices && indices.size() > 0){
			if(!indBuffer.isCreated())
				indBuffer.create(Index);
			
			indBuffer.bind();
			indBuffer.allocate((void*)indices.data(), indices.size() * sizeof(unsigned int), accessType);
		}

		mustUpdate = false;

		return true;
	}
	return false;
}

template<typename vertexType, typename dataType>
void Vertices<vertexType, dataType>::feed(unsigned int vertexAttrib){
	vertexBuffer.bind();
	glVertexAttribPointer(vertexAttrib, vertexType::CoordCount, vertexType::GLType, GL_FALSE, 0, nullptr);
}

#endif