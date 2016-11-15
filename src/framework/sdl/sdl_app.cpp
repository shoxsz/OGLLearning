#include "sdl_app.hpp"

void SDLApplication::init(SubSystem flags){
	if(SDL_Init(flags) != 0)
		throw runtime_error(SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	fps = 30;
}

void SDLApplication::quit(){
	if(window && window->isAlive())
		window->dispose();
}

void SDLApplication::run(SDLWindow* window){
    SDL_Event event;
    milliseconds now, prev(0), delta(0);
    FPSCounter fpsCounter(fps);

    if(window == nullptr)
        return;

    if(!window.isAlive())
        return;
    
    running = true;

    this->window = window;

	try{
		window->preLoop();
		while (window->isAlive()){
			fpsCounter.start();

			poll();

			now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			delta = now - prev;
			prev = now;

			window->process(delta);

			if (fpsCounter.shouldRender()){
				window->render(delta);
			}
			window->paint();
			fpsCounter.delay();
		}
		window->posLoop();
	}catch(std::exception& ex){
	}

    running = false;
}

void SDLApplication::poll(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		window->event(&event);
	}
}