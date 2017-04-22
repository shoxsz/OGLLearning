#include "application.hpp"

#include <commom\resource_manager.hpp>

#include <iostream>
#include <utils\vector.hpp>

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
		{ -0.5f, -0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },

		{ -0.5f, -0.5f, -1.0f },
		{ 0.5f, -0.5f, -1.0f },
		{ 0.5f, 0.5f, -1.0f },
		{ -0.5f, 0.5f, -1.0f }
	});
	vertices.setIndices({0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4});

	vertices.update(true);
	vertices.feed(vertexIndex);

	glEnableVertexAttribArray(colorIndex);
	colors.addVertices({
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },

		{ 1.0f, 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 0.0f, 1.0f }
	});

	colors.setIndices({ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 });

	colors.update();
	colors.feed(colorIndex);

	sprogram.loadMatrix(sprogram.getUniformLocation("projection"),
		perspective(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 10.0f));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	angleX = angleY = 0;
	zoom = -1.0f;
}

void Application::onQuit(){
	sprogram.dispose();
}

void Application::logics(milliseconds delta){
	
}

void Application::render(milliseconds delta){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*angle += delta.count() * 0.05;
	if (angle >= 360.0f)
		angle = 0.0f;*/

	sprogram.loadMatrix(sprogram.getUniformLocation("modelview"),
		rotate(angleX, 0.0f, 1.0f, 0.0f)
				.mult(rotate(angleY, 1.0f, 0.0f, 0.0f))
				.mult(translate(0.0f, 0.0f, zoom)));

	glDrawElements(GL_TRIANGLES, vertices.countIndices(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, vertices.countVertices());
}

void Application::caught(SDL_Event* event){
	switch (event->type) {
	case SDL_QUIT:
		SDLApplication::getInstance()->quit();
		break;
	case SDL_MOUSEWHEEL:
		zoom += event->wheel.y / 2.0f;
		std::cout << zoom << std::endl;
		break;
	case SDL_MOUSEMOTION:
		//se apenas o botão direito estiver pressionado
		if (SDL_BUTTON(SDL_BUTTON_RIGHT) == SDL_GetMouseState(nullptr, nullptr)) {
			angleX += event->motion.xrel;
			angleY += event->motion.yrel;
		}
		break;
	}
}