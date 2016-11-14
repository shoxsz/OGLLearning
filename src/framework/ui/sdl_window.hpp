#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <SDL.h>
#include <SDL_opengl.h>

#include "box.hpp"

class SDLApplication;
class SDLWindow;

class SDLBox : public Box{
public:

	SDLBox(SDLWindow* window) : window(window){}

	void act();

private:
	SDL_Event event;
	SDLWindow* window;
};

class SDLWindow{
public:
	friend class SDLApplication;

	SDLWindow(const SDLWindow& window) = delete;
	SDLWindow(SDLWindow&& window) = delete;
	SDLWindow() :
		window(nullptr), 
		gl(nullptr),
		creationFlags(0),
		x(0),
		y(0),
		width(0),
		height(0),
		visible(false),
		fullscreen(false),
		alive(false){}
	virtual ~SDLWindow();

	void create(bool visible = true){ create(title, x, y, width, height, visible, fullscreen); }
	void create(const std::string& title, int x, int y, int w, int h, bool visible, bool fullscreen);
	void dispose();

	void paint();

	void close(){closed();}

	void setFullscreen(bool fullscreen);
	void setTitle(const std::string& title);
	void setSize(int width, int height);
	void setPosition(int x, int y);
	void setVisibility(bool visible);

	SDLBox* getBox(){ return box.get(); }
	unsigned int getCreationFlags()const{ return creationFlags; }
	std::string& getTitle(){ return title; }
	const std::string& getTitle()const{ return title; }
	int getX()const{ return x; }
	int getY()const{ return y; }
	int getWidth()const{ return width; }
	int getHeight()const{ return height; }
	bool isVisible()const{ return visible; }
	bool isFullscreen()const{ return fullscreen; }
	bool isCreated()const{ return alive; }

protected:
	virtual void preLoop(){}
	virtual void process(milliseconds delta) = 0;
	virtual void render(milliseconds delta) = 0;
	virtual void posLoop(){}

	//SDL_QUIT or SDL_WINDOW_CLOSE has been caught
	virtual void closed(){}

private:
	void resized(int w, int h);

	SDLApplication* app;

	std::unique_ptr<SDLBox> box;
	unsigned int creationFlags;
	std::string title;
	int x, y;
	int width, height;
	bool visible, fullscreen;
	SDL_Window* window;
	SDL_GLContext gl;
	bool alive;
};

#endif