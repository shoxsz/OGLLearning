#include "application.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]){
    SDLApplication* app = SDLApplication::getInstance();
    ApplicationListenerPtr appListener(new Application);

    try{
        app->init(argc, (const char**)argv, SDLApplication::Video);
        app->setName("First concepts");
        app->setWidth(640);
        app->setHeight(640);

        app->run(appListener);

    }catch(std::exception& ex){
        SDLMessageBox::create()->showSimple(SDLMessageBox::Error, (app == nullptr ? app->getWindow() : nullptr), "Error", ex.what());
    }

    if(app)
        app->quit();

    return 0;
}