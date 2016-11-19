#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <chrono>
#include <memory>

class Scene{
public:
    virtual void begin() = 0;
    virtual void update(std::chrono::milliseconds delta) = 0;
    virtual void render(std::chrono::milliseconds delta) = 0;
    virtual void hide() = 0;

    virtual void pause(){}
    virtual void resume(){}

    virtual void event(SDL_Event* event) = 0;
};

typedef std::shared_ptr<Scene> ScenePtr;

#endif