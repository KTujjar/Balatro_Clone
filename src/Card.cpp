#include "Card.h"

Card::Card()
{
}

bool Card::Init(SDL_Renderer *r, SDL_Texture *spriteSheet, int x, int y)
{
    texture = spriteSheet;
    if(texture == nullptr)
    {
        return false;
    }
    
    textureRect =
    {
        (float)(x * 58),
        (float)(y * 76),
        58.0f,
        76.0f,
    };

    cardRank = x + 1;
    cardSuit = y;

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return true;
}

bool Card::Draw(SDL_Renderer *r, SDL_FRect position)
{
    if(texture != nullptr)
    {
        cardRect = position;
        if (!SDL_RenderTexture(r, texture, &textureRect, &cardRect)) {
            SDL_Log("Could not draw card: %s  Rank: %d", SDL_GetError(), cardRank);
            return false;
        }
    }
    else
    {
        SDL_Log("Card texture not found");
        return false;   
    }

    return true;
}

Card::~Card()
{
}