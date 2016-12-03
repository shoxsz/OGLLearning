#ifndef _SPRITE_BATCH_HPP_
#define _SPRITE_BATCH_HPP_

#include "definitions.hpp"
#include "vertices.hpp"
#include "texture.hpp"
#include "shader_program.hpp"

struct CoordAttribute2D{
    float x, y;
};

struct TextureAttribute2D{
    float u, v;
};

/*2D sprite batch*/
class SpriteBatch{
public:
	static const AttributeSpec coordAttribute;
	static const AttributeSpec texAttribute;

	static const std::string modelviewName;
	static const std::string projectionName;

    SpriteBatch():drawing(false), maxVertices(1024), coords(Dynamic), texCoords(Dynamic){
		loadDefaultProgram();
	}

	/*set the shaders to be used with the shader program, the shaders must name its attributes and uniforms as specified by this batcher */
	SpriteBatch(ShaderPtr vertexShader, ShaderPtr fragmentShader) :drawing(false), maxVertices(1024), coords(Dynamic), texCoords(Dynamic) {
		setShaders(vertexShader, fragmentShader);
	}

	/*set the shaders to be used with the shader program, it will cause the sahder program to be
	recreated, the shaders must name its attributes and uniforms as specified by this batcher */
	void setShaders(ShaderPtr vertexShader, ShaderPtr fragmentShader);

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

    unsigned int getMaxVertices()const{ return coords.countVertices(); }

private:
	void loadDefaultProgram();

    bool drawing;
    unsigned int maxVertices;

    Texture2DPtr currentTexture;
    Vertices<CoordAttribute2D> coords;
    Vertices<TextureAttribute2D> texCoords;
	ShaderProgram shaderProgram;

	Matrix3 modelviewMatrix;
	Matrix3 projectionMatrix;

	unsigned int modelviewLocal;
	unsigned int projectionLocal;
};

#endif