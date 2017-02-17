#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <sdl/sdl_app.hpp>
#include <graphics/texture_manager.hpp>
#include <graphics/shader_program.hpp>
#include <graphics/shader.hpp>
#include <graphics/vertices.hpp>

class Application : public ApplicationListener{
public:
    virtual void onStart();
    virtual void onQuit();
    virtual void logics(milliseconds delta);
    virtual void render(milliseconds delta);
    virtual void pause(){}
    virtual void resume(){}
    virtual void caught(SDL_Event* event);
private:
    ShaderProgram sprogram;
	ShaderPtr vshader, fshader;

    Texture2DPtr texture;
	Vertices<Vertex, float> coords;
	Vertices<TexturedVertex, float> texCoords;

    unsigned int samplerLocation;
	unsigned int mvMatrixLocation, pMatrixLocation;
};

#endif