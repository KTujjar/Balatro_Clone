
#pragma once
#include "Card.h"
#include <vector>
#include <memory>

class Deck
{
private:

public:

    SDL_FRect src = 
    {
        0.0f,
        0.0f,
        58.0f,
        76.0f,
    };
    
    SDL_FRect position =
    {
        120.0f,
        230.0f,
        58.0f,
        76.0f,
    };


    SDL_Texture *cardBack;
    SDL_Texture *spriteSheet;
    std::vector<std::unique_ptr<Card>> cards;
    void Init(SDL_Renderer *r, const char* filename);
    void Discard(int index);
    void Render(SDL_Renderer *r);
    Deck();
    ~Deck();
};

