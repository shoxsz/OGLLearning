#ifndef _VERTICES_HPP_
#define _VERTICES_HPP_

#include "buffer_object.hpp"
#include "utils/point.hpp"
#include "utils/rect.hpp"
#include "enums.hpp"

#include <GL/glew.h>
#include <vector>

struct Vertex{
	float x, y, z;
};

template<typename vertexType = Vertex, typename dataType = float>
class Vertices{
public:
	Vertices():mustUpdate(false) {}
	Vertices(AccessType accessType):mustUpdate(false), accessType(accessType){}

	void addVertex(const vertexType& vertex);
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

	void clear(){
		posBuffer.dispose();
		indBuffer.dispose();
		coords.clear();
		indices.clear();
	}

	void setAccessType(AccessType accessType) {
		this->accessType = accessType;
	}

	AccessType getAccessType()const{ return accessType; }
	unsigned int countVertices()const{ return coords.size() / sizeof(vertexType); }
	const std::vector<unsigned int>& getIndices()const{ return indices; }
	const std::vector<float>& getCoords()const{ return coords; }

protected:
	AccessType accessType;

	bool mustUpdate;

	BufferObject posBuffer;
	BufferObject indBuffer;
	std::vector<dataType> coords;
	std::vector<unsigned int> indices;
};

template<typename vertexType, typename dataType>
void Vertices<vertexType, dataType>::addVertex(const vertexType& vertex){
	unsigned int oldSize = coords.size();
	//the division is >= 1 since vertexType is(must be) composed only of dataType data
	coords.insert(coords.end(), sizeof(vertexType) / sizeof(dataType), 0);
	//raw copy of the data
	memcpy(coords.data() + oldSize, &vertex, sizeof(vertexType));
	mustUpdate = true;
}

template<typename vertexType, typename dataType>
bool Vertices<vertexType, dataType>::update(bool useIndices){
	if(mustUpdate && coords.size() > 0){
		if(!posBuffer.isCreated())
			posBuffer.create(Array);

		posBuffer.bind();
		posBuffer.allocate((void*)coords.data(), coords.size() * sizeof(dataType), accessType);

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

#endif