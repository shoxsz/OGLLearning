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

	/*glEnableVertexAttribArray(vertexIndex);
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
	texCoords.feed(texIndex);*/

	std::vector<ModelPtr> models;
	ResourceManager::loadSKN("cassiopeia.skn", models);

	Model model;
	ResourceManager::loadOBJ("cassiopeia_model.obj", model);

	thresh = models[0];
	glEnableVertexAttribArray(vertexIndex);
	thresh->getCoords().update(true);
	thresh->getCoords().feed(vertexIndex);

	glEnableVertexAttribArray(texIndex);
	thresh->getTexCoords().update(true);
	thresh->getTexCoords().feed(texIndex);

	texture = ResourceManager::loadTexture("cassiopeia_tex.dds", false);
	texture->setFiltering(Nearest, Nearest);
	texture->bind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	angleX = angleY = 90.0f;
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

	sprogram.loadMatrix(sprogram.getUniformLocation("projection"),
		perspective(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f));

	float radius = zoom;
	float pi = std::acos(-1);
	float xz = pi * angleX / 180.0f;
	float xy = pi * angleY / 180.0f;
	float sin_xz = std::sin(xz);
	float cos_xz = std::cos(xz);
	float sin_xy = std::sin(xy);
	float cos_xy = std::cos(xy);

	float x = radius*sin_xy*cos_xz;
	float z = radius*sin_xy*sin_xz;
	float y = radius*cos_xy;

	/*sprogram.loadMatrix(sprogram.getUniformLocation("modelview"), 
		lookAt({ x , y, z }, {movex, movey, 0.0f}, {0.0f, 1.0f, 0.0f}));*/

	sprogram.loadMatrix(sprogram.getUniformLocation("modelview"),
		rotate(angleX, 0.0f, 1.0f, 0.0f)
				.mult(rotate(angleY, 1.0f, 0.0f, 0.0f))
				.mult(translate(movex, movey, zoom)));

	glDrawElements(GL_TRIANGLES, thresh->getCoords().countIndices(), GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::caught(SDL_Event* event){
	switch (event->type) {
	case SDL_QUIT:
		SDLApplication::getInstance()->quit();
		break;
	case SDL_MOUSEWHEEL:
		zoom += event->wheel.y * 4;
		break;
	case SDL_MOUSEMOTION:
		//se apenas o botão direito estiver pressionado
		if (SDL_BUTTON(SDL_BUTTON_RIGHT) == SDL_GetMouseState(nullptr, nullptr)) {
			angleX += -event->motion.xrel;
			angleY += -event->motion.yrel;
		}
		else if (SDL_BUTTON(SDL_BUTTON_LEFT) == SDL_GetMouseState(nullptr, nullptr)) {
			movex += event->motion.xrel;
			movey += -event->motion.yrel;
		}
		break;
	}
}