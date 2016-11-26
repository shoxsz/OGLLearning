#ifndef _SPRITE_BATCH_HPP_
#define _SPRITE_BATCH_HPP_

#include "buffer_object.hpp"
#include "vertices.hpp"

struct SpriteVertex{
    float x, y;
};

struct TextureVertex{
    float u, v;
};

/*2D sprite batch*/
class SpriteBatch{
public:

private:
    Vertices<SpriteVertex> vertex;
    Vertices<TextureVertex> texture;
};

#endif