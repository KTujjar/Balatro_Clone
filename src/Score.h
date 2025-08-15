#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h>
#include "Global.h"

class Score
{
private:
    
public:

    SDL_Texture *texture;
    SDL_FRect scoreRect;
    SDL_FRect srcRect;
    
    void Init(SDL_Renderer *r);
    bool Render(SDL_Renderer *r);
    Score();
    ~Score();
};
