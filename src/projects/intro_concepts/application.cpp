#include "application.hpp"

#include <commom\resource_manager.hpp>

void Application::onStart(){
	vshader = ResourceManager::loadShader("v_intro.txt");
	fshader = ResourceManager::loadShader("f_intro.txt");
		
	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link();
}

void Application::onQuit(){

}

void Application::logics(milliseconds delta){

}

void Application::render(milliseconds delta){

}

void Application::caught(SDL_Event* event){

}