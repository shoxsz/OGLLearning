#include "sdl_window.hpp"

#include <chrono>

#include "sdl_app.hpp"

void SDLBox::act(){
	SDL_Event* event = SDLApplication::getInstance().getEvent();

	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_WINDOW_EVENT{
				switch(event.window.type){
					case SDL_WINDOW_CLOSE:
						window->close();
					break;
				}
			break;
			}
		}
	}
}

SDLWindow::~SDLWindow(){
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(gl);
}

void SDLWindow::create(const std::string& title, int x, int y, int w, int h, bool visible, bool fullscreen){
	creationFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if (visible)
		creationFlags |= SDL_WINDOW_SHOWN;
	if (fullscreen)
		creationFlags |= SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title.c_str(), x, y, w, h, creationFlags);

	if (window == nullptr)
		throw std::runtime_error(SDL_GetError());

	gl = SDL_GL_CreateContext(window);

	if (gl == nullptr)
		throw std::runtime_error(SDL_GetError());

	this->x = x;
	this->y = y;
	this->visible = visible;
	this->fullscreen = fullscreen;
	this->box.reset(new SDLBox(this));
	this->alive = true;
	resized(w, h);
}

void SDLWindow::dispose(){
	alive = false;
}

void SDLWindow::paint(){
	SDL_GL_SwapWindow(window);
}

void SDLWindow::setFullscreen(bool fullscreen){
	this->fullscreen = fullscreen;
	if (window)
		SDL_SetWindowFullscreen(window, creationFlags);
}

void SDLWindow::setTitle(const std::string& title){
	this->title = title;
	if (window)
		SDL_SetWindowTitle(window, title.c_str());
}

void SDLWindow::setSize(int width, int height){
	if (window != nullptr)
		SDL_SetWindowSize(window, width, height);
	else{
		this->width = width;
		this->height = height;
	}
}

void SDLWindow::setPosition(int x, int y){
	this->x = x;
	this->y = y;
	if (window != nullptr)
		SDL_SetWindowPosition(window, x, y);
}

void SDLWindow::setVisibility(bool visible){
	this->visible = visible;
	if (window && visible)
		SDL_ShowWindow(window);
	else
		SDL_HideWindow(window);
}

void SDLWindow::resized(int w, int h){
	this->width = w;
	this->height = h;
	/*Call some graphics function to change the viewport...*/
}