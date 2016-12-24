#ifndef _SDL_BOX_HPP_
#define _SDL_BOX_HPP_

#include "ui/box.hpp"

#include <GL/glew.h>
#include <SDL.h>

class SDLBox : public Box{
public:
    SDLBox(SDL_Event* event, SDL_Window* window){setEvent(event); setWindow(window);}
    SDLBox():event(nullptr){}

    virtual void poll();

    void setEvent(SDL_Event* event){
        this->event = event;
    }

    void setWindow(SDL_Window* window){
        this->window = window;
    }

    const SDL_Window* getWindow()const{
        return window;
    }

private:
	void resized(int w, int h);

    SDL_Event* event;
    SDL_Window* window;
};

#endif