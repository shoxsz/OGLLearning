#include "sdl_app.hpp"

void SDLApplication::init(SubSystem flags){
	if(SDL_Init(flags) != 0)
		throw runtime_error(SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	fps = 30;
}

void SDLApplication::quit(){
	running = false;
}

void SDLApplication::run(const std::string& name, int width, int height, ApplicationListener* appListener){
    SDL_Event event;
    milliseconds now, prev(0), delta(0);
    FPSCounter fpsCounter(fps);

    if(window == nullptr)
        return;

    if(!window.isAlive())
        return;
    
    running = true;

	try{
		this->name = name;
		this->width = width;
		this->height = height;
		
		createWindow();
		appListener->onStart();
		while (running){
			fpsCounter.start();

			while(SDL_PollEvent(&event)){
				appListener->event(&event);
			}

			now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			delta = now - prev;
			prev = now;

			appListener->process(delta);

			if (fpsCounter.shouldRender()){
				appListener->render(delta);
			}
			window->paint();
			fpsCounter.delay();
		}
		appListener->onQuit();
	}catch(std::exception& ex){
	}

    running = false;
}

void SDLApplication::createWindow(){
	window = new SDLWindow();

	//default window configs
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
