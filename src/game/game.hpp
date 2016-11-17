#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "sdl_app.hpp"
#include "scene.hpp"

#include <stack>

class Game : public ApplicationListener{
public:
    void onStart();
    void onQuit();
    void logics(milliseconds delta);
    void render(milliseconds delta);
    void pause();
    void resume();
    void caught(SDL_Event* event);
private:
};

#endif