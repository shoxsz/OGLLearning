#include "sprite_batch.hpp"

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

void SpriteBatch::preLink(){
	glBindAttribLocation(programId, POSITION_ATTR, "v_position");
	glBindAttribLocation(programId, TEXTURE_ATTR, "v_texture");
}