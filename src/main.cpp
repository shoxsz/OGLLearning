#include "game.hpp"
#include "sdl_app.hpp"

int main(int argc, char* argv[]){
    SDLApplicationPtr app;
    Game game;

    app.reset(SDLApplication::getInstance());
    app->init();
    app->run("Battle for tanks!", 640, 640, &game);

    return 0;
}