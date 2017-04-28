#include "application.hpp"

#include <commom\resource_manager.hpp>

#include <iostream>
#include <utils\vector.hpp>

void Application::onStart(){
	Mat4x4f mvMatrix, pMatrix;
	GLint Plocation, Mlocation;
	const GLuint vertexIndex = 0, texIndex = 1, normalIndex = 2;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	vshader = ResourceManager::loadShader("simple-vs.txt", ShaderType::VertexShader);
	fshader = ResourceManager::loadShader("simple-fs.txt", ShaderType::FragmentShader);

	vshader->compile();
	fshader->compile();

	sprogram.setVertexShader(vshader);
	sprogram.setFragmentShader(fshader);
	sprogram.link({ {"vertex", vertexIndex}, {"tex", texIndex }, {"normal", normalIndex} });
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

	glEnableVertexAttribArray(texIndex);
	texCoords.addVertices({
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },

		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	});
	texCoords.setIndices({ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 });

	texCoords.update(true);
	texCoords.feed(texIndex);

	/*ResourceManager::loadModel("thresh_model.obj", thresh);
	glEnableVertexAttribArray(vertexIndex);
	thresh.getCoords().update(true);
	thresh.getCoords().feed(vertexIndex);

	glEnableVertexAttribArray(texIndex);
	thresh.getTexCoords().update(true);
	thresh.getTexCoords().feed(texIndex);*/

	texture = ResourceManager::loadTexture("thresh_tex.dds", false);
	texture->setFiltering(Nearest, Nearest);
	texture->bind();

	/*sprogram.loadMatrix(sprogram.getUniformLocation("projection"),
		perspective(45.0f, 1920.0f / 1080.0f , 1.0f, 100.0f));*/

	sprogram.loadMatrix(sprogram.getUniformLocation("projection"),
		perspective(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	angleX = angleY = 0;
	zoom = -10.0f;
	movex = movey = 0.0f;
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
				.mult(translate(movex, movey, zoom)));

	glDrawElements(GL_TRIANGLES, vertices.countIndices(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::caught(SDL_Event* event){
	switch (event->type) {
	case SDL_QUIT:
		SDLApplication::getInstance()->quit();
		break;
	case SDL_MOUSEWHEEL:
		zoom += event->wheel.y / 1.0f;
		break;
	case SDL_MOUSEMOTION:
		//se apenas o botão direito estiver pressionado
		if (SDL_BUTTON(SDL_BUTTON_RIGHT) == SDL_GetMouseState(nullptr, nullptr)) {
			angleX += -event->motion.xrel;
			angleY += -event->motion.yrel;
		}
		else if (SDL_BUTTON(SDL_BUTTON_LEFT) == SDL_GetMouseState(nullptr, nullptr)) {
			movex += event->motion.xrel / 10.0f;
			movey += -event->motion.yrel / 10.0f;
		}
		break;
	}
}