#pragma once    
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


class Card
{
private:

    SDL_Texture * texture;



public:
    Card();
    ~Card();
    bool Draw(SDL_Renderer *r, SDL_FRect position);
    bool Load(SDL_Renderer *r, const char *filename);

    SDL_FRect textureRect =
    {
        0.f,
        0.f,
        100.f,  //78 - 21
        100.f,  //87 - 12
    };
    
    SDL_FRect cardRect =
    {
        21.f,
        12.f,
        57.f,
        75.f,
    };

    SDL_FRect handPosition;

    //where the card is interactable
    SDL_FRect bounds;

    //Hover Animation
    float popAmount = 0.0f;


    float cardLeft = cardRect.x  - textureRect.x;
    float cardRight = textureRect.w - (cardRect.x +cardRect.w);

};

