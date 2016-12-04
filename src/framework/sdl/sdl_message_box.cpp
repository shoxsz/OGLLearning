#include "sdl_message_box.hpp"

#include "sdl_error.hpp"

int SDLMessageBox::show(Type type){
    show(nullptr, type);
}

int SDLMessageBox::show(const SDLWindowPtr window, Type type){
    int id;
    SDL_MessageBoxData msgData;
    std::vector<SDL_MessageBoxButtonData> buttons;

    msgData.flags = type;
    msgData.window = window == nullptr ? nullptr : window->getWindow();
    msgData.title = title.c_str();
    msgData.message = message.c_str();
    msgData.numbuttons = buttons.size();
    
    if(buttons.size() > 0){
        for(MessageBoxButton& button : this->buttons){
            buttons.push_back({0, button.id, button.text.c_str()});
        }

		if (!defaultReturn.text.empty())
			buttons.push_back({ DefaultReturn, defaultReturn.id, defaultReturn.text.c_str() });
		if (!defaultEscape.text.empty())
			buttons.push_back({ DefaultEscape, defaultEscape.id, defaultEscape.text.c_str() });

        msgData.buttons = buttons.data();
    }else{
        msgData.buttons = nullptr;
    }

    if(colors.size() > 0)
        msgData.colorScheme = (SDL_MessageBoxColorScheme*)colors.data();
    else
        msgData.colorScheme = nullptr;

    if(SDL_ShowMessageBox(&msgData, &id) < 0)
        throw SDLError();

    return id;
}

void SDLMessageBox::showSimple(Type type, const SDLWindowPtr window, const std::string& title, const std::string message){
    if(SDL_ShowSimpleMessageBox(type, title.c_str(), message.c_str(), window == nullptr ? nullptr : window->getWindow()) < 0)
        throw SDLError();
}

SDLMessageBox& SDLMessageBox::setTitle(const std::string& title){
    this->title = title;
}

SDLMessageBox& SDLMessageBox::setMessage(const std::string& message){
    this->message = message;
}

SDLMessageBox& SDLMessageBox::addButtons(const std::vector<MessageBoxButton>& buttons){
    for(const MessageBoxButton& button : buttons){
        this->buttons.push_back(button);
    }
}

SDLMessageBox& SDLMessageBox::setDefaultReturn(const MessageBoxButton& button){
    this->defaultReturn = button;
}

SDLMessageBox& SDLMessageBox::setDefaultEscape(const MessageBoxButton& button){
    this->defaultReturn = button;
}

SDLMessageBox& SDLMessageBox::setColor(unsigned int index, MessageBoxColor color){
    this->colors[index] = color;
}

SDLMessageBox& SDLMessageBox::setColors(const std::vector<MessageBoxColor>& colors){
    this->colors = colors;
}