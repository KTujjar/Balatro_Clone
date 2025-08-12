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

void Hand::checkHover(int mouseX, int mouseY) {
    hoveredCardIndex = -1;
    SDL_FPoint mousePoint = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
    for (size_t i = 0; i < hand.size(); i++) {
        if (SDL_PointInRectFloat(&mousePoint, &hand[i]->bounds)) {
            hoveredCardIndex = i;
            //SDL_Log("%d", hoveredCardIndex);
            break;
        }
    }
}

void Hand::updateHoverAnimation(double delta) {
    for (size_t i = 0; i < hand.size(); i++) {
        if ((int)i == hoveredCardIndex) {
            hand[i]->popAmount += 2.0f * delta; // grow
            if (hand[i]->popAmount > maxPop) hand[i]->popAmount = maxPop;
        } else {
            hand[i]->popAmount -= 2.0f * delta; // shrink back
            if (hand[i]->popAmount < 0) hand[i]->popAmount = 0;
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
    float calculatedPosition;
    for(int i = 0; i < hand.size(); i++)
    {

        calculatedPosition = (120.0f - (hand[i]->cardLeft)) + ((cardWidth - overlapWidth) * (i));

        hand[i]->handPosition = 
        {
            calculatedPosition, 
            220.0f, 
            100.0f, 
            100.0f,
        };

        //Makes last card interactable throughout full width
        if(i == (hand.size() - 1))
        {
            hand[i]->bounds = 
            {
                calculatedPosition + hand[i]->cardLeft,
                220.0f,
                hand[i]->cardRect.w,
                100.0f,
            };
        }
        else
        {
            hand[i]->bounds = 
            {
                calculatedPosition + hand[i]->cardLeft,
                220.0f,
                cardWidth - overlapWidth,
                100.0f,
            };
        }

        float scale = 1.0f + hand[i]->popAmount; // e.g., popAmount = 0.2 means +20% size
        SDL_FRect drawPos = hand[i]->handPosition;
        drawPos.w *= scale;
        drawPos.h *= scale;
        drawPos.x -= (drawPos.w - hand[i]->handPosition.w) / 2;
        drawPos.y -= (drawPos.h - hand[i]->handPosition.h) / 2;
        hand[i]->Draw(r, drawPos);

        //SDL_Log("calculatedPosition: %f", calculatedPosition);
        //hand[i]->Draw(r, hand[i]->handPosition);

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