#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <chrono>

class Scene{
public:
    virtual void begin() = 0;
    virtual void update(std::chrono::milliseconds delta) = 0;
    virtual void render(std::chrono::milliseconds delta) = 0;
    virtual void hide() = 0;
};

#endif