#include "sdl_error.hpp"
#include "sdl_window.hpp"

#include <chrono>

SDLWindow::~SDLWindow(){
	if(window)
		dispose();
}

void SDLWindow::create(const std::string& title, int x, int y, int w, int h, bool visible, bool fullscreen){
	creationFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	if (visible)
		creationFlags |= SDL_WINDOW_SHOWN;
	if (fullscreen)
		creationFlags |= SDL_WINDOW_FULLSCREEN;
	if(minimized)
		creationFlags |= SDL_WINDOW_MINIMIZED;
	if(maximized)
		creationFlags |= SDL_WINDOW_MAXIMIZED;

	window = SDL_CreateWindow(title.c_str(), x, y, w, h, creationFlags);

	if (window == nullptr)
		throw SDLError();

	gl = SDL_GL_CreateContext(window);

	if (gl == nullptr)
		throw SDLError();

	this->x = x;
	this->y = y;
	this->visible = visible;
	this->fullscreen = fullscreen;
	this->alive = true;
}

void SDLWindow::dispose(){
	if(window){
		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(gl);
		alive = false;
	}
}

void SDLWindow::paint(){
	SDL_GL_SwapWindow(window);
}

void SDLWindow::maximize(){
	this->maximized = true;
	if(window)
		SDL_MaximizeWindow(window);
}

void SDLWindow::minimize(){
	this->maximized = true;
	if(window)
		SDL_MaximizeWindow(window);
}

void SDLWindow::restore(){
	if(window)
		SDL_RestoreWindow(window);
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
	this->width = width;
	this->height = height;
	if (window)
		SDL_SetWindowSize(window, width, height);
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