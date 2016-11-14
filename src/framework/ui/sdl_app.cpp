#include "sdl_app.hpp"

void SDLApplication::init(SubSystem flags){
	if(SDL_Init(flags) != 0)
		throw runtime_error(SDL_GetError());

	/*start opengl*/
}

void SDLApplication::quit(){
	if(window && window->isAlive())
		window->dispose();

	/*disable opengl*/
}

void SDLApplication::run(SDLWindow* window){
    SDL_Event event;
    milliseconds now, prev(0), delta(0);
    FPSCounter fpsCounter(60);

    if(window == nullptr)
        return;

    if(!window.isAlive())
        return;
    
    running = true;

    this->window = window;

	try{
		window->preLoop();
		while (window->alive){
			fpsCounter.start();

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