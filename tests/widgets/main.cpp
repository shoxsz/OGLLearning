#include "ui/widget.hpp"
#include "utils/color.hpp"
#include "utils/rect.hpp"

#include <GL\glew.h>
#include <SDL.h>
#undef main
#include <SDL_opengl.h>

#include "sdl_box.hpp"

#include <iostream>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)

class GLDrawer : public Drawer{
public:
    virtual void draw(Widget* widget){
        Color color;
        Rect quad = widget->getRect();
		float borderTopDown = quad.height() * 0.01f;
		float borderLeftRight = quad.width() * 0.01f;

        if(widget->isPressed()){
            color.r = 0.0f;
            color.g = 0.0f;
            color.b = 1.0f;
        }else if(widget->isCovered()){
            color.r = 0.0f;
            color.g = 1.0f;
            color.b = 0.0f;
        }else if(widget->isDragged()){
            color.r = 1.0f;
            color.g = 1.0f;
            color.b = 0.0f;
        }else{
            color.r = 1.0f;
            color.g = 0.0f;
            color.b = 0.0f;
        }

        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex2i(quad.left, quad.top);
            glVertex2i(quad.right, quad.top);
            glVertex2i(quad.right, quad.bottom);
            glVertex2i(quad.left, quad.bottom);

			glColor3f(color.r, color.g, color.b);
			glVertex2f(quad.left + borderLeftRight, quad.top + borderTopDown);
			glVertex2f(quad.right - borderLeftRight, quad.top + borderTopDown);
			glVertex2f(quad.right - borderLeftRight, quad.bottom - borderTopDown);
			glVertex2f(quad.left + borderLeftRight, quad.bottom - borderTopDown);
        glEnd();
    }
};

void start(SDL_Window** window, SDL_GLContext* gl){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::runtime_error(SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    *window = SDL_CreateWindow("Widget Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    if(*window == nullptr){
        throw std::runtime_error(SDL_GetError());
    }

    *gl = SDL_GL_CreateContext(*window);

    if(*gl == nullptr){
        throw std::runtime_error(SDL_GetError());
    }
}

void createWidgets(Widget* root) {
	WidgetPtr w1(new Widget());

	w1->makeClickable(true);
	w1->makeDraggable(true);
	w1->makeEditable(false);
	w1->setPosition({ 10, 10 });
	w1->setSize({ 100, 100 });
	w1->setDrawer(root->getDrawer());
	w1->setOnMouseMove([] (Widget& widget, const MouseMoveEvent& move) {
		std::cout << "from: (" << move.getSourcePosition().x << ", " << move.getSourcePosition().y << ") to: (" << move.getTargetPosition().x << ", " << move.getTargetPosition().y << ")" << std::endl;
	});

	root->addChild(w1);
}

int main(){
    SDL_Window* window;
    SDL_GLContext gl;
    SDL_Event event;
	DrawerPtr drawer;
    std::unique_ptr<SDLBox> box;
    bool running = true;

    WidgetPtr root;

    try{
        start(&window, &gl);

		drawer.reset(new GLDrawer());

		//create root widget
		root.reset(new Widget());
		root->makeClickable(true);
		root->makeDraggable(false);
		root->makeEditable(true);
		root->setPosition({ 0, 0 });
		root->setSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
		root->setDrawer(drawer);

		//create box
		box.reset(new SDLBox(&event, window));
		box->setRoot(root);

		//create childs
		createWidgets(root.get());

		//gl configs...
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW_MATRIX);
		glLoadIdentity();
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        while(running){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        running = false;
                        break;
                    default:
                        box->poll();
                        break;
                }
            }
            glClear(GL_COLOR_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION_MATRIX);
			glLoadIdentity();
			glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);

            root->draw();

            SDL_GL_SwapWindow(window);
        }

    }catch(std::runtime_error& ex){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ex.what(), nullptr);
    }

	SDL_GL_DeleteContext(gl);
	SDL_DestroyWindow(window);

	SDL_Quit();

    return 0;
}