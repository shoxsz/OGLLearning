#ifndef _SPRITE_BATCH_HPP_
#define _SPRITE_BATCH_HPP_

#include "vertices.hpp"
#include "texture.hpp"

struct SpriteVertex{
    float x, y;
};

struct TextureVertex{
    float u, v;
};

/*This will use shader program to render all the data*/

/*2D sprite batch*/
class SpriteBatch{
public:
    SpriteBatch():drawing(false), maxVertices(1024){}

    //max vertices to use in the vbo's, when the limit is reached the vertex will be sent to the gpu
    void setMaxVertices(unsigned int vertices){
        this->maxVertices = vertices;
    }

    //begin the drawing process for the specified texture
    void begin(Texture2DPtr texture);
    void end();

    //draw the current texture inside the rect
    void draw(Rect& rect);

    //draw the specified src from the texture inside the dst
    void drawRect(Rect& src, Rect& dst);

    unsigned int getMaxVertices()const{ return vertices; }

private:
    bool drawing;
    unsigned int maxVertices;

    Texture2DPtr currentTexture;
    Vertices<SpriteVertex> vertex;
    Vertices<TextureVertex> texture;
};

#endif