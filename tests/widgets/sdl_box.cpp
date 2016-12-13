#include "sdl_box.hpp"

void SDLBox::poll(){
    switch(event->type){
	case SDL_WINDOWEVENT:{
		switch (event->window.event) {
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		case SDL_WINDOWEVENT_RESTORED:
		case SDL_WINDOWEVENT_MAXIMIZED:
			resized(event->window.data1, event->window.data2);
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		this->root->mouseDown({
			event->button.button == SDL_BUTTON_LEFT,	//left
			event->button.button == SDL_BUTTON_RIGHT,	//right
			event->button.button == SDL_BUTTON_MIDDLE,	//middle
			Point(event->button.x, event->button.y),
			event->button.clicks,
			true
		});
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		this->root->mouseUp({
			event->button.button == SDL_BUTTON_LEFT,
			event->button.button == SDL_BUTTON_RIGHT,
			event->button.button == SDL_BUTTON_MIDDLE,
			Point(event->button.x, event->button.y),
			event->button.clicks,
			false
		});
		break;
	}
	case SDL_MOUSEMOTION: {
		unsigned int mouse = SDL_GetMouseState(NULL, NULL);

		this->root->mouseMove({
			(mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) == SDL_BUTTON_LEFT,
			(mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) == SDL_BUTTON_RIGHT,
			(mouse & SDL_BUTTON(SDL_BUTTON_MIDDLE)) == SDL_BUTTON_MIDDLE,
			Point(event->motion.x, event->motion.y),
			Point(event->motion.x + event->motion.xrel, event->motion.y + event->motion.yrel)
		});
		break;
	}
	case SDL_MOUSEWHEEL: {
		int x, y;
		unsigned int mouse = SDL_GetMouseState(&x, &y);

		this->root->mouseScroll({
			(mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) == SDL_BUTTON_LEFT,
			(mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) == SDL_BUTTON_RIGHT,
			(mouse & SDL_BUTTON(SDL_BUTTON_MIDDLE)) == SDL_BUTTON_MIDDLE,
			Point(x, y),
			event->wheel.x,
			event->wheel.y
		});
		break;
	}
	case SDL_KEYDOWN: {
		if (keyboardFocus != nullptr) {
			this->root->keyDown({
				(unsigned char)event->key.keysym.sym,
				(unsigned char)event->key.keysym.mod,
				event->key.repeat,
				KeyboardEvent::KeyDown
			});
		}
		break;
	}
	case SDL_KEYUP: {
		if (keyboardFocus != nullptr) {
			keyboardFocus->keyUp({
				(unsigned char)event->key.keysym.sym,
				(unsigned char)event->key.keysym.mod,
				event->key.repeat,
				KeyboardEvent::KeyUp
			});
		}
		break;
	}
	case SDL_TEXTINPUT: {
		if (keyboardFocus != nullptr) {
			keyboardFocus->textInput({
				event->text.text
			});
		}
		break;
	}
    }
}

void SDLBox::resized(int w, int h) {
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, w, h, 0, -1, 1);
	glViewport(0, 0, w, h);
}