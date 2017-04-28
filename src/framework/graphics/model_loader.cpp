#include "model_loader.hpp"

#include <utils/string.hpp>

void ModelLoader::load(const std::string& file, Model& model) {
	std::ifstream ifile(file);
	std::string line;
	std::vector<std::string> words;

	if (!ifile.is_open())
		throw std::runtime_error("Failed to load file: " + file);

	this->model = &model;

	while (!ifile.eof()) {
		std::getline(ifile, line);
		split(line, " ", words);

		if (words[0] == "v") {
			loadVertices(ifile, words);
		}
		else if (words[0] == "vt") {
			loadTextures(ifile, words);
		}
		else if (words[0] == "vn") {
			loadNormals(ifile, words);
		}
		else if (words[0] == "f") {
			loadFaces(ifile, words);
		}
	}

	//cria os indices
	const std::vector<ModelFace>& faces = model.getFaces();
	for (const ModelFace& mface : faces) {
		model.getCoords().addIndice(mface.attribs[0][0]-1);
		model.getCoords().addIndice(mface.attribs[1][0]-1);
		model.getCoords().addIndice(mface.attribs[2][0]-1);

		model.getTexCoords().addIndice(mface.attribs[0][1]-1);
		model.getTexCoords().addIndice(mface.attribs[1][1]-1);
		model.getTexCoords().addIndice(mface.attribs[2][1]-1);

		model.getNormals().addIndice(mface.attribs[0][2]-1);
		model.getNormals().addIndice(mface.attribs[1][2]-1);
		model.getNormals().addIndice(mface.attribs[2][2]-1);
	}
}

void ModelLoader::loadVertices(std::ifstream& file, std::vector<std::string>& line) {
	Vertex coords = {
		std::atof(line[1].c_str()),
		std::atof(line[2].c_str()),
		std::atof(line[3].c_str())
	};

	model->getCoords().addVertex(coords);
}

void ModelLoader::loadNormals(std::ifstream& file, std::vector<std::string>& line) {
	Vertex coords = {
		std::atof(line[1].c_str()),
		std::atof(line[2].c_str()),
		std::atof(line[3].c_str())
	};

	model->getCoords().addVertex(coords);
}

void ModelLoader::loadTextures(std::ifstream& file, std::vector<std::string>& line) {
	TexturedVertex coords = {
		std::atof(line[1].c_str()),
		std::atof(line[2].c_str())
	};

	model->getTexCoords().addVertex(coords);
}

void ModelLoader::loadFaces(std::ifstream& file, std::vector<std::string>& line) {
	std::vector<std::string> v0, v1, v2;
	ModelFace modelFace;

	split(line[1], "/", v0);
	split(line[2], "/", v1);
	split(line[3], "/", v2);

	if (v0.size() > 1)
		modelFace.hasTexture = true;
	if (v0.size() > 2)
		modelFace.hasNormals = true;

	modelFace.attribs[0][0] = std::atof(v0[0].c_str());
	if (modelFace.hasTexture)
		modelFace.attribs[0][1] = std::atof(v0[1].c_str());
	if (modelFace.hasNormals)
		modelFace.attribs[0][2] = std::atof(v0[2].c_str());

	modelFace.attribs[1][0] = std::atof(v1[0].c_str());
	if (modelFace.hasTexture)
		modelFace.attribs[1][1] = std::atof(v1[1].c_str());
	if (modelFace.hasNormals)
		modelFace.attribs[1][2] = std::atof(v1[2].c_str());

	modelFace.attribs[2][0] = std::atof(v2[0].c_str());
	if (modelFace.hasTexture)
		modelFace.attribs[2][1] = std::atof(v2[1].c_str());
	if (modelFace.hasNormals)
		modelFace.attribs[2][2] = std::atof(v2[2].c_str());

	if (v0[1].size() == 0)
		modelFace.hasTexture = false;

	model->getFaces().push_back(modelFace);
}