#ifndef _VERTICES_HPP_
#define _VERTICES_HPP_

#include <SDL_opengl.h>
#include <vector>

#include "buffer_object.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"

/*Holds a buffer of vertices of a generic vertexType, these vertices are stored in a vector of dataType*/
template<typename vertexType = Vertex, typename dataType = float>
class Vertices{
public:
	Vertices() :
		verticesCount(0),
		vertexSize(sizeof(vertexType))
	{}

	void addVertex(const vertexType& vertex);
    void addTriangle(const vertexType& a, const vertexType& b, const vertexType& c);
    void addRectangle(const vertexType& a, const vertexType& b, const vertexType& c, const vertexType& d);

	unsigned int countVertices() const { return verticesCount; }
	std::vector<unsigned int> getIndices(){return indices;}
	const std::vector<float> buffer getVertices()const{return buffer;}

protected:
	unsigned int vertexSize;
	unsigned int verticesCount;
	std::vector<unsigned int> indices;
	std::vector<dataType> buffer;
};

template<typename vertexType = Vertex>
void Vertices<vertexType>::addVertex(const vertexType& vertex){
	unsigned int offset = buffer.size() * sizeof(dataType);
	buffer.insert(0, vertexSize);
	memcpy(buffer.data() + size, &vertex, vertexSize);
	verticesCount++;
}

template<typename vertexType = Vertex>
void Vertices<vertexType>::addTriangle(const vertexType& a, const vertexType& b, const vertexType& c){
	addVertex(a);
	addVertex(b);
	addVertex(c);
}

template<typename vertexType = Vertex>
void Vertices<vertexType>::addRectangle(const vertexType& a, const vertexType& b, const vertexType& c, const vertexType& d){
	addVertex(a);
	addVertex(b);
	addVertex(c);
	addVertex(d);
}

#endif