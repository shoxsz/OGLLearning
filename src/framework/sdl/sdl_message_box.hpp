#ifndef _SDL_MESSAGE_BOX_HPP_
#define _SDL_MESSAGE_BOX_HPP_

#include <SDL.h>

#include <vector>
#include <string>

class SDLMessageBox{
public:
    friend class SDLWindow;

    enum Type{
        Error = SDL_MESSAGEBOX_ERROR,
        Warning = SDL_MESSAGEBOX_WARNING,
        Information = SDL_MESSAGEBOX_INFORMATION
    };

    SDLMessageBox(SDL_Window* window):window(window){}
    ~SDLMessageBox();

    SDLMessageBox& button(const std::string& text, int id){
        internalAddButton(0, text, id);
        return *this;
    }

    SDLMessageBox& enterButton(const std::string& text, int id){
        internalAddButton(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, text, id);
        return *this;
    }

    SDLMessageBox& escButton(const std::string& text, int id){
        internalAddButton(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, text, id);
        return *this;
    }

    SDLMessageBox& setTitle(const std::string& title){
        this->title = title;
    }

    SDLMessageBox& setText(const std::string& text){
        this->text = text;
    }

    int show(Type type);

    std::string& getTitle()const{return title;}
    std::string& getText()const{return text;}

private:
    void internalAddButton(int flags, const std::string& text, int id);

    SDL_Window* window;
    std::string title;
    std::string text;
    std::vector<SDL_MessageBoxButtonData> buttons;
};
#endif