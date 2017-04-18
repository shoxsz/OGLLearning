#include "application.hpp"

#include <commom\resource_manager.hpp>

void Application::onStart(){
	Mat4x4f mvMatrix, pMatrix;
	GLint Plocation, Mlocation;
	const GLuint vertexIndex = 0, colorIndex = 1;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	vshader = ResourceManager::loadShader("simple-vs.txt", ShaderType::VertexShader);
	fshader = ResourceManager::loadShader("simple-fs.txt", ShaderType::FragmentShader);

	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link({ {"vertex", vertexIndex}, {"color", colorIndex} });
	sprogram.bind();

	glEnableVertexAttribArray(vertexIndex);
	vertices.addVertices({
		{ -1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 1.0f },

		/*{ -1.0f, -1.0f, 2.0f },
		{ 1.0f, -1.0f, 2.0f },
		{ 1.0f, 1.0f, 2.0f },
		{ 1.0f, 1.0f, 2.0f },
		{ -1.0f, 1.0f, 2.0f },
		{ -1.0f, -1.0f, 2.0f },

		{ -1.0f, -1.0f, 1.0f },
		{ -1.0f, -1.0f, 2.0f },
		{ -1.0f, 1.0f, 2.0f },
		{ -1.0f, 1.0f, 2.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 1.0f },

		{ 1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, 2.0f },
		{ 1.0f, 1.0f, 2.0f },
		{ 1.0f, 1.0f, 2.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f }*/
	});

	vertices.update();
	vertices.feed(vertexIndex);

	glEnableVertexAttribArray(colorIndex);
	colors.addVertices({
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },

		/*{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },

		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },

		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 1.0f, 1.0f }*/
	});

	colors.update();
	colors.feed(colorIndex);

	sprogram.loadMatrix(sprogram.getUniformLocation("modelview"),
		rotate(10.0f, 1.0f, 1.0f, 0.0f));

	sprogram.loadValue(sprogram.getUniformLocation("left"), -3.0f);
	sprogram.loadValue(sprogram.getUniformLocation("right"), 3.0f);
	sprogram.loadValue(sprogram.getUniformLocation("bottom"), -3.0f);
	sprogram.loadValue(sprogram.getUniformLocation("top"), 3.0f);
	sprogram.loadValue(sprogram.getUniformLocation("near"), 1.0f);
	sprogram.loadValue(sprogram.getUniformLocation("far"), 10.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, vertices.countVertices());
}

void Application::caught(SDL_Event* event){
	switch (event->type) {
	case SDL_QUIT:
		SDLApplication::getInstance()->quit();
		break;
	}
}