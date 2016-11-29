#ifndef _SDL_APPLICATION_HPP_
#define _SDL_APPLICATION_HPP_

#include <SDL.h>
#include <SDL_image.h>

#include <memory>

#include "fps_counter.hpp"

#include "sdl_error.hpp"
#include "sdl_window.hpp"

class ApplicationListener{
public:
    virtual void onStart() = 0;
    virtual void onQuit() = 0;
    virtual void logics(milliseconds delta) = 0;
    virtual void render(milliseconds delta) = 0;
    virtual void pause() = 0;	//not being used yet
    virtual void resume() = 0;	//not being used yet
    virtual void caught(SDL_Event* event) = 0;
};

/*Notes: this is a one window application, since it's an desktop application 
maybe i chould give more control over the window to the application listener...*/
class SDLApplication{
private:
    static SDLApplication* app;
public:
    static SDLApplication* getInstance(){
        if(app == nullptr)
            app = new SDLApplication();
        return app;
    }

	enum SubSystem {
		Timer = SDL_INIT_TIMER,
		Audio = SDL_INIT_AUDIO,
		Video = SDL_INIT_VIDEO,
		Joystick = SDL_INIT_JOYSTICK,
		Haptic = SDL_INIT_HAPTIC,
		GameController = SDL_INIT_GAMECONTROLLER,
		Events = SDL_INIT_EVENTS,
		All = SDL_INIT_EVERYTHING
	};

	SDLApplication(const SDLApplication& app) = delete;
    SDLApplication& operator=(const SDLApplication& app) = delete;
    ~SDLApplication(){dispose();}

    void init(SubSystem flags = All);
    void quit();

    void run(const std::string& name, int width, int height, ApplicationListener* appListener);

	void setFPS(unsigned int fps) { this->fps = fps; }

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

typedef std::shared_ptr<SDLApplication> SDLApplicationPtr;

#endif