#include "Card.h"

Card::Card()
{
}

bool Card::Load(SDL_Renderer *r, const char *filename)
{
    texture = IMG_LoadTexture(r, filename);
    if(texture == nullptr)
    {
        return false;
    }
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return true;
}

bool Card::Draw(SDL_Renderer *r, SDL_FRect position)
{
    if(texture != nullptr)
    {
        if (!SDL_RenderTexture(r, texture, &textureRect, &position)) {
            SDL_Log("RenderTextureRotated failed: %s", SDL_GetError());
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
    SDL_DestroyTexture(texture);
}