#ifndef _SDL_APPLICATION_HPP_
#define _SDL_APPLICATION_HPP_

/*it is a good idea to include this file above all to gurantee that glew will be included before any gl.h*/
#include <gl\glew.h>

#include "utils/fps_counter.hpp"
#include "sdl_error.hpp"
#include "sdl_window.hpp"
#include "sdl_message_box.hpp"

#include <SDL.h>
#include <SDL_image.h>

#include <memory>

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

typedef std::shared_ptr<ApplicationListener> ApplicationListenerPtr;

class SDLApplication{
public:
    static SDLApplication* getInstance(){
        static SDLApplication* app = new SDLApplication();
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

    void init(unsigned int argc = 0, const char* argv[] = nullptr, SubSystem flags = All);
    void quit();

    void setName(const std::string& name){
        this->name = name;
    }

    void setWidth(int width){
        this->width = width;
    }

    void setHeight(int height){
        this->height = height;
    }

    void run(ApplicationListenerPtr appListener);

	void setFPS(unsigned int fps) { this->fps = fps; }

	bool isRunning()const { return running; }
	unsigned int getFPS()const { return fps; }
	SDLWindowPtr getWindow()const { return window; }
	const std::string& getName()const { return name; }
	int getWidth()const { return width; }
	int getHeight()const { return height;; }
	const std::string& getAppDir()const { return app_dir; }
	const std::vector<std::string>& getArgs()const { return argv; }
private:
    SDLApplication():
        running(false),
        fps(30),
        window(nullptr),
        name("SDLApplication"),
        width(512),
        height(512){}

    void createWindow();
    void dispose();

    bool running;
    unsigned int fps;
    SDLWindowPtr window;

    std::string name;
    int width, height;

	std::string app_dir;
	std::vector<std::string> argv;
};

typedef std::shared_ptr<SDLApplication> SDLApplicationPtr;

#endif