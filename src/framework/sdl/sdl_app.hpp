#ifndef _SDL_APPLICATION_HPP_
#define _SDL_APPLICATION_HPP_

#include <SDL.h>

#include <utils\fps_counter.hpp>

#include "sdl_error.hpp"
#include "sdl_window.hpp"

class ApplicationListener{
public:
    virtual void onStart() = 0;
    virtual void onQuit() = 0;
    virtual void logics(milliseconds delta) = 0;
    virtual void render(milliseconds delta) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void caught(SDL_Event* event) = 0;
};

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

    SDLApplication(const SDLApplication& app) = delete;
    SDLApplication& operator=(const SDLApplication& app) = delete;
    ~SDLApplication(){dispose();}

    void setFPS(unsigned int fps){this->fps = fps;}

    void init(SubSystem flags = All);
    void quit();

    void run(const std::string& name, int width, int height, ApplicationListener* appListener);

    bool isRunning()const{return running;}
    unsigned int getFPS()const{return fps;}
    SDLWindow* getWindow()const{return window;}
    std::string getName()const{return name;}
    int getWidth()const{return width;}
    int getHeight()const{return height;}
private:
    SDLApplication():
        running(false),
        fps(30),
        window(nullptr){}

    void createWindow();
    void dispose();

    bool running;
    unsigned int fps;
    SDLWindow* window;
    std::string name;
    int width, height;
};

#endif