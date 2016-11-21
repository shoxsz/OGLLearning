#ifndef _SPRITE_BATCH_HPP_
#define _SPRITE_BATCH_HPP_

#include "buffer_object.hpp"
#include "vertices.hpp"

struct SpriteVertex{
	enum{ UseTexture = true };
    float x, y;
	float u, v;
};

/*2D sprite batch*/
class SpriteBatch{
public:
private:
    BufferObject vbo;
    Vertices<SpriteVertice> vertices;
};

#endif