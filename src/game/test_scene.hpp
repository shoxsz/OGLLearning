#ifndef _TEST_SCENE_HPP_
#define _TEST_SCENE_HPP_

#include "scene.hpp"

class TestScene : public TestScene{
public:
    void begin();
    void update(std::chrono::milliseconds delta);
    void render(std::chrono::milliseconds delta);
    void hide();

    void pause();
    void resume();

    void event(SDL_Event* event);
};

#endif