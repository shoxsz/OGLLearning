#include "sprite_batch.hpp"

#include <graphics/shader.hpp>
#include <sstream>

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

	vshader->load(vertexShader);
	fshader->load(vertexShader);

	setShaders(vshader, fshader);
}