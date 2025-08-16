#include "Deck.h"

Deck::Deck()
{
}

void Deck::Init(SDL_Renderer *r, const char* filename)
{
    spriteSheet = IMG_LoadTexture(r, filename);
    cardBack = IMG_LoadTexture(r, "../assets/Cards/cardBack.png");

    SDL_SetTextureScaleMode(cardBack, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(spriteSheet, SDL_SCALEMODE_NEAREST);
    
    for(int x = 0; x < 13; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            cards.push_back(std::make_unique<Card>());
            if(!cards.back()->Init(r, spriteSheet, x, y))
            {
                SDL_Log("Could not load card into deck");
            }
        }
    }
}

void Deck::Discard(int index)
{
    cards.erase(cards.begin() + index);
}

void Deck::Render(SDL_Renderer *r)
{
    SDL_FRect src = 
    {
        0.0f,
        0.0f,
        58.0f,
        76.0f,
    };
    
    SDL_FRect position =
    {
        550.0f,
        240.0f,
        58.0f,
        76.0f,
    };

    if(!SDL_RenderTexture(r, cardBack, &src, &position))
    {
        SDL_Log("Could not render deck back");
    }
}

Deck::~Deck()
{
    if (spriteSheet) {
        SDL_DestroyTexture(spriteSheet);
        spriteSheet = nullptr;
    }
    if (cardBack) {
        SDL_DestroyTexture(cardBack);
        cardBack = nullptr;
    }
}