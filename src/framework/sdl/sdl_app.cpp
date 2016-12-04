#include "sdl_app.hpp"

#include "sdl_message_box.hpp"

SDLApplication* SDLApplication::app = nullptr;

void SDLApplication::init(SubSystem flags){
	if (SDL_Init(flags) != 0)
		throw SDLError();

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
		throw SDLError();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

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
		SDLMessageBox::create()->showSimple(SDLMessageBox::Error, nullptr, "Error", ex.what());
	}

    running = false;
}

void SDLApplication::createWindow(){
	window = new SDLWindow();

	window->setTitle(name);
	window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->setSize(width, height);
	window->create();
}

void SDLApplication::dispose(){
	if(window && window->isAlive()){
		window->dispose();
		delete window;
	}
}
