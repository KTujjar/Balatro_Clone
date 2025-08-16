#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h>
#include "Global.h"
#include <string>
#include <cstring>

class Score
{
private:
    
public:
    //Text
    SDL_Color textColor;
    float textW, textH;
    TTF_Font *font;
    SDL_FRect textRect;
    float fontSize;
    SDL_Texture *textTexture = nullptr;
    SDL_FRect textMovedRect;
    SDL_FRect tempTextRect;

    //Score Box
    SDL_Texture *texture;
    SDL_FRect scoreRect;
    SDL_FRect srcRect;
    
    //Score
    int score = 0;
    int lastScore = -1;

    void Init(SDL_Renderer *r);
    bool Render(SDL_Renderer *r);
    void updateScoreText(SDL_Renderer *r, int fontSize, SDL_Color tColor);
    Score();
    ~Score();
};
