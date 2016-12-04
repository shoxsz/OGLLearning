#ifndef _SDL_MESSAGE_BOX_HPP_
#define _SDL_MESSAGE_BOX_HPP_

#include <SDL.h>

#include <vector>
#include <string>

#include "sdl_window.hpp"
#include "definitions.hpp"

struct MessageBoxButton{
    int id;
    std::string text;
};

struct MessageBoxColor{
    unsigned char r, g, b;
};

class SDLMessageBox{
private:
	enum ButtonType {
		DefaultReturn = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
		DefaultEscape = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
	};
public:
	enum Type {
		Error = SDL_MESSAGEBOX_ERROR,
		Warning = SDL_MESSAGEBOX_WARNING,
		Information = SDL_MESSAGEBOX_INFORMATION
	};

	static SDLMessageBoxPtr create() { return SDLMessageBoxPtr(new SDLMessageBox()); }

    SDLMessageBox(){}

    int show(Type type);
    int show(const SDLWindowPtr window, Type type);
    void showSimple(Type type, const SDLWindowPtr window, const std::string& title, const std::string message);

    SDLMessageBox& setTitle(const std::string& title);
    SDLMessageBox& setMessage(const std::string& message);
    SDLMessageBox& addButtons(const std::vector<MessageBoxButton>& buttons);
    SDLMessageBox& setDefaultReturn(const MessageBoxButton& button);
    SDLMessageBox& setDefaultEscape(const MessageBoxButton& button);
    SDLMessageBox& setColor(unsigned int index, MessageBoxColor color);
    SDLMessageBox& setColors(const std::vector<MessageBoxColor>& colors);

private:
    std::string title;
    std::string message;

    MessageBoxButton defaultReturn, defaultEscape;
    std::vector<MessageBoxButton> buttons;
    std::vector<MessageBoxColor> colors;
};

#endif