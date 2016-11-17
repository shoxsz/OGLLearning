#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <SDL.h>
#include <SDL_opengl.h>

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
		maximized(false),
		minimized(false),
		visible(false),
		fullscreen(false),
		alive(false){}
		
	virtual ~SDLWindow();

	void create(bool visible = true){ create(title, x, y, width, height, visible, fullscreen); }
	void create(const std::string& title, int x, int y, int w, int h, bool visible, bool fullscreen);
	void dispose();

	void paint();

	void maximize();
	void minimize();
	void restore();
	void setFullscreen(bool fullscreen);
	void setTitle(const std::string& title);
	void setSize(int width, int height);
	void setPosition(int x, int y);
	void setVisibility(bool visible);

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

private:
	unsigned int creationFlags;
	std::string title;
	int x, y;
	int width, height;
	bool maximized, minimized;
	bool visible, fullscreen;
	SDL_Window* window;
	SDL_GLContext gl;
	bool alive;
};

#endif