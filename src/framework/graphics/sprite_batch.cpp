#include "sprite_batch.hpp"

#include <graphics/shader.hpp>
#include <sstream>

const AttributeSpec SpriteBatch::coordAttribute = AttributeSpec("coord", 0);
const AttributeSpec SpriteBatch::texAttribute = AttributeSpec("texCoord", 1);

const std::string SpriteBatch::modelviewName = "modelview_matrix";
const std::string SpriteBatch::projectionName = "projection_matrix";

void SpriteBatch::setShaders(ShaderPtr vertexShader, ShaderPtr fragmentShader) {
	shaderProgram.dispose();
	shaderProgram.setVertexShader(vertexShader);
	shaderProgram.setFragmentShader(fragmentShader);
	shaderProgram.link({coordAttribute, texAttribute});

	modelviewLocal = shaderProgram.getUniformLocation(SpriteBatch::modelviewName);
	projectionLocal = shaderProgram.getUniformLocation(SpriteBatch::projectionName);
}

void SpriteBatch::begin(Texture2DPtr texture){
    if(drawing && texture != currentTexture)
        end();
    
    currentTexture = texture;

    drawing = true;
}

void SpriteBatch::end(){

}

void SpriteBatch::draw(Rect& rect){

}

void SpriteBatch::drawRect(Rect& src, Rect& dst){

}

void SpriteBatch::loadDefaultProgram() {
	std::stringstream vertexShader;
	std::stringstream fragmentShader;
	ShaderPtr vshader(new Shader());
	ShaderPtr fshader(new Shader());

	vshader->load(vertexShader, ShaderType::VertexShader);
	fshader->load(vertexShader, ShaderType::FragmentShader);

	setShaders(vshader, fshader);
}