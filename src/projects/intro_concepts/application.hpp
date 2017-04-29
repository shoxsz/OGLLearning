#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <sdl\sdl_app.hpp>
#include <graphics\shader_program.hpp>
#include <graphics\shader.hpp>
#include <graphics\vertices.hpp>
#include <graphics\texture.hpp>
#include <graphics\obj_loader.hpp>

class Application : public ApplicationListener{
public:
    virtual void onStart();
    virtual void onQuit();
    virtual void logics(milliseconds delta);
    virtual void render(milliseconds delta);
    virtual void pause(){}	//not being used yet
    virtual void resume(){}	//not being used yet
    virtual void caught(SDL_Event* event);
private:
	ShaderPtr vshader, fshader;
    ShaderProgram sprogram;
	//ShaderPtr vshader, fshader;
	GLuint vao;
	Vertices<Vertex, float> vertices;
	Vertices<TexturedVertex, float> texCoords;
	Vertices<Vertex, float> normals;

	ModelPtr thresh;

	Texture2DPtr texture;

	float angleX;
	float angleY;
	float zoom;
	float movex, movey;
};

#endif