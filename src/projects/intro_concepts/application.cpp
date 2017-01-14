#include "application.hpp"

#include <commom/resource_manager.hpp>

#define MODELVIEW_MATRIX "mvMatrix"
#define PROJECTION_MATRIX "pMatrix"

#define COORD_POS (0)

void Application::onStart(){
	vshader = ResourceManager::loadShader("simple-vs.txt", ShaderType::VertexShader);
	fshader = ResourceManager::loadShader("simple-fs.txt", ShaderType::FragmentShader);
		
	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link({ {"coordPos", COORD_POS } });
	sprogram.bind();

	//mvMatrixLocation = sprogram.getUniformLocation(MODELVIEW_MATRIX);
	//pMatrixLocation = sprogram.getUniformLocation(PROJECTION_MATRIX);

	vertices.setAccessType(AccessType::Static);

	vertices.addVertex({ -1.0f, -1.0f, 0.0f });
	vertices.addVertex({ 1.0f, 1.0f, 0.0f });
	vertices.addVertex({ 0.0f, 1.0f, 0.0f });

	//update the vertices in the vbo
	vertices.update();

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){
	glClear(GL_COLOR_BUFFER_BIT);

	//enable & load the vbo data to the vertices attributes
	glEnableVertexAttribArray(COORD_POS);
	glVertexAttribPointer(COORD_POS, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	//draw the vertices
	glDrawArrays(GL_TRIANGLES, 0, vertices.countVertices());
}

void Application::caught(SDL_Event* event){
	switch(event->type){
		case SDL_QUIT:
			SDLApplication::getInstance()->quit();
		break;
	}
}