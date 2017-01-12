#include "sdl_app.hpp"

#include "sdl_message_box.hpp"

#include <iostream>

void SDLApplication::init(SubSystem flags){
	if (SDL_Init(flags) != 0)
		throw SDLError();

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
		throw SDLError();

	fps = 30;
}

void SDLApplication::quit(){
	running = false;
}

void SDLApplication::run(ApplicationListenerPtr appListener){
    SDL_Event event;
    milliseconds now, prev(0), delta(0);
    FPSCounter fpsCounter(fps);
    
	try{
		createWindow();

		//load opengl functions
		glewExperimental = true;
		GLenum status = glewInit();
		if (status) {
			std::cout << glewGetErrorString(status);
			throw std::runtime_error("Failed to load opengl functions.");
		}

		appListener->onStart();
		running = true;
		while (running){
			fpsCounter.start();

			while(SDL_PollEvent(&event)){
				appListener->caught(&event);
			}

			now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			delta = now - prev;
			prev = now;

			appListener->logics(delta);

			if (fpsCounter.shouldRender()){
				appListener->render(delta);
			}
			window->paint();
			fpsCounter.delay();
		}
		appListener->onQuit();
	}catch(std::exception& ex){
		running = false;
		SDLMessageBox::create()->showSimple(SDLMessageBox::Error, nullptr, "Error", ex.what());
	}
}

void SDLApplication::createWindow(){
	window.reset(new SDLWindow());

	window->setTitle(name);
	window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->setSize(width, height);
	window->create();
}

void SDLApplication::dispose(){
	if(window && window->isAlive()){
		window->dispose();
	}
}
