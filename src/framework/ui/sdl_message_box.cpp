#include "sdl_message_box.hpp"

SDLMessageBox::~SDLMessageBox(){
    for(auto& btt : buttons){
        delete [] btt.text;
    }
}

SDLMessageBox& SDLMessageBox::internalAddButton(int flags, const std::string& text, int id){
    char* btt_text = new char[text.size()];

    memcpy(btt_text, text.c_str(), text.size());
    btt_text[text.size()] = 0;

    buttons.push_back({flags, id, btt_text});
}

int show(){
    int buttonId;
    if(SDL_ShowMessageBox({}, &buttonId) == -1){
        throw std::runtime_error(SDL_GetError());
    }
    return buttonId;
}

int showSimple(Type type, const std::string& title, const std::string& text){

}

