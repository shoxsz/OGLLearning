#include "application.hpp"

#include <commom\resource_manager.hpp>

void Application::onStart(){
	vshader = ResourceManager::loadShader("simple-vs.txt");
	fshader = ResourceManager::loadShader("simple-fs.txt");
		
	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link();
	sprogram.bind();

	//objects controls
	angle = 0.0f;
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){

}

void Application::caught(SDL_Event* event){

}