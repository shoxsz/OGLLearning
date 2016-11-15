#ifndef _SDL_APPLICATION_HPP_
#define _SDL_APPLICATION_HPP_

#include <SDL.h>

#include <utils\fps_counter.hpp>

#include "sdl_window.hpp"

class SDLApplication{
private:
    SDLApplication* app;
public:
    static SDLApplication getInstance(){
        if(app = nullptr)
            app = new SDLApplication();
        return app;
    }

    enum SubSystem{
        Timer = SDL_INIT_TIMER,
        Audio = SDL_INIT_AUDIO,
        Video = SDL_INIT_VIDEO,
        Joystick = SDL_INIT_JOYSTICK,
        Haptic = SDL_INIT_HAPTC ,
        GameController = SDL_INIT_GAMECONTROLLER,
        Events = SDL_INIT_EVENTS,
        All = SDL_INIT_EVERYTHING
    }
    
    SDLApplication(): running(false), window(nullptr){}

    void setFPS(unsigned int fps){this->fps = fps;}

    void init(SubSystem flags = All);
    void quit();

    void run(SDLWindow* window);

    bool isRunning()const{return running;}
    unsigned int getFPS()const{return fps;}
    SDLWindow* getWindow()const{return window;}
private:
    void poll();

    bool running;
    unsigned int fps;
    SDLWindow* window;
};

#endif