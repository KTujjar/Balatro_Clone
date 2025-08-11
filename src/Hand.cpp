#include "Hand.h"

int Hand::handCount = 0;

Hand::Hand()
{
    //Hand not showing because its only being called once. Need to find a way to store hand and keep it rendered?
    //Store hand cards in a card vector and use that to always render hand. Then create draw and discard functions handle
    //array when cards are drawn and discarded.
}

void Hand::Init(SDL_Renderer* r)
{
    if (hand.size() < maxHandSize) {
        Draw(r, maxHandSize - hand.size());
    }
}

void Hand::Draw(SDL_Renderer *r, int drawSize)
{
    for(int i = 0; i < drawSize; i++)
    {
        hand.push_back(std::make_unique<Card>());
        
        if(!hand.back()->Load(r, "../assets/Cards/Ace_Heart.png"))
        {
            SDL_Log("Could not load card. Error: %s", SDL_GetError());
        }

    }
}

void Hand::RenderHandArea(SDL_Renderer *r)
{
    SDL_FRect position = {120, 230, 400, 100};

    if(!SDL_SetRenderDrawColor(r, 33, 64, 49, 255))
    {
        SDL_Log("Failed to color hand background");
    }

    if(!SDL_RenderFillRect(r, &position))
    {
        SDL_Log("Failed to load hand");
    }

}

void Hand::RenderHandCards(SDL_Renderer *r)
{
    float cardWidth = 400.f/maxHandSize;
    float overlapWidth = hand[0]->cardRect.w / cardWidth;
    for(int i = 0; i < hand.size(); i++)
    {
        float calculatedPosition;
        if(i == 0)
        {
            calculatedPosition = (120.0f - (hand[i]->cardLeft)); //- (cardWidth - overlapWidth);
        }
        else
        {
            calculatedPosition = (120.0f - (hand[i]->cardLeft)) + ((cardWidth - overlapWidth) * (i));
        }

        //SDL_Log("calculatedPosition: %f", calculatedPosition);
        hand[i]->Draw(r, {calculatedPosition, 220.0f, 100.0f, 100.0f});

        handCount+=1;
    }

}

void Hand::Render(SDL_Renderer *r)
{
   RenderHandArea(r);
   RenderHandCards(r);
}

Hand::~Hand()
{

}