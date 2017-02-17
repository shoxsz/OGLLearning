#include "application.hpp"

#include <iostream>
#include <commom/resource_manager.hpp>

#define MODELVIEW_MATRIX ("mvMatrix")
#define PROJECTION_MATRIX ("pMatrix")
#define SAMPLER ("tex")

#define COORDS (0)
#define TEX_COORDS (1)

void Application::onStart(){
	vshader = ResourceManager::loadShader("simple-vs.txt", ShaderType::VertexShader);
	fshader = ResourceManager::loadShader("simple-fs.txt", ShaderType::FragmentShader);
		
	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link({ {"coord", COORDS }, {"texCoord", TEX_COORDS}});
	sprogram.bind();

	samplerLocation = sprogram.getUniformLocation(SAMPLER);
	sprogram.loadValue(samplerLocation, 0);

	coords.addVertices({
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f}
	});
	coords.update();

	texCoords.addVertices({
			{0.0f, 0.0f}, 
			{1.0f, 0.0f}, 
			{1.0f, 1.0f}, 
			{1.0f, 1.0f}, 
			{0.0f, 1.0f},
			{0.0f, 0.0f}
	});
	texCoords.update();

	texture = ResourceManager::loadTexture("crate.jpg", false);
	texture->setFiltering(Nearest, Nearest);
	texture->bind();

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(COORDS);
	coords.feed(COORDS);

	glEnableVertexAttribArray(TEX_COORDS);
	texCoords.feed(TEX_COORDS);

	//draw the vertices
	std::cout << "aqui" << std::endl;
	glDrawArrays(GL_TRIANGLES, 0, coords.countVertices());
	std::cout << "aqui" << std::endl;
}

void Application::caught(SDL_Event* event){
	switch(event->type){
		case SDL_QUIT:
			SDLApplication::getInstance()->quit();
		break;
	}
}