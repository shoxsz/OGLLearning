#include "sdl_message_box.hpp"

#include "sdl_error.hpp"

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

int SDLMessageBox::show(Type type){
    int buttonId;
    SDL_MessageBoxData data = {type, window, title.c_str(), text.c_str(), buttons.size(), buttons.data(), nullptr};

    if(SDL_ShowMessageBox(&data, &buttonId) == -1){
        throw SDLError();
    }
    return buttonId;
}

