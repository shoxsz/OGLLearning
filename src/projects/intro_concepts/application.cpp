#include "application.hpp"

#include <commom\resource_manager.hpp>

#define MODELVIEW_MATRIX "mvMatrix"
#define PROJECTION_MATRIX "pMatrix"

#define COORD_POS (0)

void Application::onStart(){
	vshader = ResourceManager::loadShader("simple-vs.txt");
	fshader = ResourceManager::loadShader("simple-fs.txt");
		
	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link({ {"coordPos", COORD_POS } });
	sprogram.bind();

	mvMatrixLocation = sprogram.getUniformLocation(MODELVIEW_MATRIX);
	pMatrixLocation = sprogram.getUniformLocation(PROJECTION_MATRIX);

	vertices.setAccessType(AccessType::Static);

	vertices.addVertex({ -0.5f, -0.5f, 0.0f });
	vertices.addVertex({ 0.5f, -0.5f, 0.0f });
	vertices.addVertex({ 0.5f, 0.5f, 0.0f });
	vertices.addVertex({ -0.5f, 0.5f, 0.0f });
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){
	vertices.update();
}

void Application::caught(SDL_Event* event){

}