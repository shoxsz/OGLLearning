#ifndef _GAME_WINDOW_HPP_
#define _GAME_WINDOW_HPP_

#include "sdl_window.hpp"

class GameWindow : public SDLWindow{
public:
    ~GameWindow();

	void event(SDL_Event* ev);
	void preLoop();
	void process(milliseconds delta);
	void render(milliseconds delta);
	void posLoop();

private:
};

#endif