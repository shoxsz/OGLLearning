#include "application.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]){
    SDLApplication* app = SDLApplication::getInstance();
    ApplicationListenerPtr appListener(new Application);

    try{
        app->init(argc, (const char**)argv, SDLApplication::Video);
        app->setName("First concepts");
        app->setWidth(600);
        app->setHeight(600);

        app->run(appListener);

    }catch(std::exception& ex){
        SDLMessageBox::create()->showSimple(SDLMessageBox::Error, (app == nullptr ? app->getWindow() : nullptr), "Error", ex.what());
    }

    return 0;
}