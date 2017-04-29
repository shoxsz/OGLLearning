#include "skn_loader.hpp"

#include <fstream>
#include <utils/binary_reader.hpp>
#include <iostream>

struct SKN_Header {
	unsigned char magic[4];
	short version;
	short matsExist;	//material header exist? 1 or 0
};

struct SKN_MaterialHeader {
	char name[64];	//nome do material
	unsigned int startVertex;
	unsigned int numVertices;
	unsigned int startIndex;
	unsigned int numIndices;
};

struct SKN_MetaDataBlock {
	int unknown;//v4 only
	unsigned int numIndices;
	unsigned int numVertices;
	unsigned char metadata[48];	//??? version for only
};

struct SKN_IndexData {
	short buffer;
	short index;
};

struct SKN_VertexData {
	float position[3];
	unsigned char boneIndices[4];
	float boneWeights[4];
	float normal[3];
	float texCoords[2];
};

struct SKN_File {
	SKN_Header header;
	unsigned int numMats;				//only valid if header.matsExist > 0
	SKN_MaterialHeader* matsHeader;		//only valid if header.matsExist > 0
	SKN_MetaDataBlock metadata;
	SKN_IndexData* indexData;
	SKN_VertexData* vertexData;
	int endTab[3];						//only for version >= 2
};

void assert_skn(bool expression, const std::string& description = "Failed to load file!") {
	if (expression == false) {
		throw std::runtime_error(description);
	}
}

void SKNLoader::load(const std::string& file, std::vector<ModelPtr>& models) {
	SKN_File skn;
	std::ifstream stream;

	stream.open(file);
	assert_skn(stream.is_open());

	BinaryReader reader(stream);

	//header
	reader.read(&skn.header, sizeof(skn.header));

	
	//materials
	if (skn.header.matsExist > 0) {
		skn.numMats = reader.get<unsigned int>();
		//std::cout << "Number of materials: " << skn.numMats << std::endl;

		skn.matsHeader = new SKN_MaterialHeader[skn.numMats];
		for (unsigned int i = 0; i < skn.numMats; i++) {
			reader.read(&skn.matsHeader[i], sizeof(SKN_MaterialHeader));
		}
	}

	//metadata
	if (skn.header.version == 1 || skn.header.version == 2) {
		skn.metadata.numIndices = reader.get<unsigned int>();
		skn.metadata.numVertices = reader.get<unsigned int>();
	}
	else if (skn.header.version == 4) {
		reader.read(&skn.metadata, sizeof(skn.metadata));
	}

	//indices
	skn.indexData = new SKN_IndexData[skn.metadata.numIndices];
	for (unsigned int i = 0; i < skn.metadata.numIndices; i++) {
		reader.read(&skn.indexData[i], sizeof(SKN_IndexData));
	}

	//vertices
	skn.vertexData = new SKN_VertexData[skn.metadata.numVertices];
	for (unsigned int i = 0; i < skn.metadata.numVertices; i++) {
		reader.read(&skn.vertexData[i], sizeof(SKN_VertexData));
	}

	if (skn.header.version >= 2) {
		reader.read(&skn.endTab, sizeof(int)*3);
	}

	/*build the models for each material*/
	ModelPtr model(new Model());
	for (unsigned int i = 0; i < skn.numMats; i++) {
		//load indices
		for (unsigned int c = skn.matsHeader[i].startIndex; c < skn.matsHeader[i].numIndices; c++) {
			model->getCoords().addIndice(skn.indexData[c].buffer);
			model->getCoords().addIndice(skn.indexData[c].index);
			model->getNormals().addIndice(skn.indexData[c].buffer);
			model->getNormals().addIndice(skn.indexData[c].index);
			model->getNormals().addIndice(skn.indexData[c].buffer);
			model->getTexCoords().addIndice(skn.indexData[c].index);
		}

		//load vertices
		for (unsigned int c = skn.matsHeader[i].startVertex; c < skn.matsHeader[i].numVertices; c++) {
			model->getCoords().addVertex({
				skn.vertexData[c].position[0],
				skn.vertexData[c].position[1],
				skn.vertexData[c].position[2] });

			model->getNormals().addVertex({
				skn.vertexData[c].normal[0],
				skn.vertexData[c].normal[1],
				skn.vertexData[c].normal[2] });

			model->getTexCoords().addVertex({
				skn.vertexData[c].texCoords[0],
				skn.vertexData[c].texCoords[1]});

			/*bone information comes here...*/
		}
		models.push_back(model);
	}

	if(skn.header.matsExist > 0)
		delete[] skn.matsHeader;
	delete[] skn.indexData;
	delete[] skn.vertexData;
}