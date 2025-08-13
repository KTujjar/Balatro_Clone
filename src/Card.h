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
    bool Init(SDL_Renderer *r, SDL_Texture *spriteSheet, int x, int y);

    SDL_FRect textureRect;

    SDL_FRect cardRect;

    SDL_FRect handPosition;

    //where the card is interactable
    SDL_FRect bounds;

    //Hover Animation
    float popAmount = 0.0f;
    float selectSpeed = 0.0f;

    bool selected = false;  

    int cardValue;

};

