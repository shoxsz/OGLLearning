#ifndef _SDL_ERROR_HPP_
#define _SDL_ERROR_HPP_

#include <SDL.h>

#include <stdexcept>

class SDLError : public std::runtime_error{
public:
    SDLError() : runtime_error(SDL_GetError()) {}
};

#endif