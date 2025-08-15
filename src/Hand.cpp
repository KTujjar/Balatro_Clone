#include "Hand.h"

int Hand::handCount = 0;

Hand::Hand()
{
    //Hand not showing because its only being called once. Need to find a way to store hand and keep it rendered?
    //Store hand cards in a card vector and use that to always render hand. Then create draw and discard functions handle
    //array when cards are drawn and discarded.
}

//Initializes the hand
void Hand::Init(SDL_Renderer* r, Deck *d)
{
    deck = d;
    if (hand.size() < maxHandSize) {
        Draw(r, maxHandSize - hand.size());
    }
}

//Draws cards based on amount of cards in hand
void Hand::Draw(SDL_Renderer *r, int drawSize)
{
    for(int i = 0; i < drawSize; i++)
    {
        srand(getpid());
        int randomNum = rand() % deck->cards.size();
        hand.push_back(std::move(deck->cards[randomNum]));
        deck->Discard(randomNum);
    }
}

//Checks if card is hovered
bool Hand::checkHover(int mouseX, int mouseY) {
    hoveredCardIndex = -1;
    SDL_FPoint mousePoint = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
    for (size_t i = 0; i < hand.size(); i++) {
        if (SDL_PointInRectFloat(&mousePoint, &hand[i]->bounds)) {
            hoveredCardIndex = i;
            return true;
        }
    }
    return false;
}

//Selects hovered card
void Hand::checkSelected(int mouseX, int mouseY)
{
    if(checkHover(mouseX, mouseY))
    {   
        if(hand[hoveredCardIndex]->selected)
        {
            hand[hoveredCardIndex]->selected = false;
            selectedAmount -=1;
        }
        else if(selectedAmount < 5)
        {
            hand[hoveredCardIndex]->selected = true;
            selectedAmount +=1;
        }
    }
}

//Handles update of hover animation
void Hand::updateHoverAnimation(double delta) {
    for (size_t i = 0; i < hand.size(); i++) {
        if ((int)i == hoveredCardIndex) {
            hand[i]->popAmount += 3.0f * delta; // grow
            if (hand[i]->popAmount > maxPop) hand[i]->popAmount = maxPop;
        } else {
            hand[i]->popAmount -= 3.0f * delta; // shrink back
            if (hand[i]->popAmount < 0) hand[i]->popAmount = 0;
        }
    }
}

//Handles update of select animation
void Hand::updateSelectAnimation(double delta) {
    for (size_t i = 0; i < hand.size(); i++) {
        if (hand[(int)i]->selected) {
            hand[i]->selectSpeed += 3.0f * delta; // grow
            if (hand[i]->selectSpeed > maxSelectPosition) hand[i]->selectSpeed = maxSelectPosition;
        } else {
            hand[i]->selectSpeed -= 3.0f * delta; // shrink back
            if (hand[i]->selectSpeed < maxSelectPosition) hand[i]->selectSpeed = maxSelectPosition;
        }
    }
}

//Handles all hand updates
void Hand::Update(double delta)
{
    updateHoverAnimation(delta);
    updateSelectAnimation(delta);
}

//Renders the rectangle for the hand
void Hand::RenderHandArea(SDL_Renderer *r)
{
    SDL_FRect position = {120, 230, 400, 100};

    if(!SDL_SetRenderDrawColor(r, 34, 64, 49, 255))
    {
        SDL_Log("Failed to color hand background");
    }

    if(!SDL_RenderFillRect(r, &position))
    {
        SDL_Log("Failed to load hand");
    }

}

//Render the cards in hand
void Hand::RenderHandCards(SDL_Renderer *r)
{
    float cardWidth = 400.f/maxHandSize;
    float overlapWidth = hand[0]->textureRect.w / cardWidth;
    float calculatedPosition;
    for(int i = 0; i < hand.size(); i++)
    {
        if (!hand[i]) 
        {
            SDL_Log("Card is not valid");
            continue;
        }


        calculatedPosition = (120.0f) + ((cardWidth - overlapWidth) * (i));

        hand[i]->handPosition = 
        {
            calculatedPosition, 
            240.0f, 
            58.0f, 
            76.0f,
        };

        //Makes last card interactable throughout full width
        if(i == (hand.size() - 1))
        {
            hand[i]->bounds = 
            {
                calculatedPosition,
                220.0f,
                hand[i]->textureRect.w,
                100.0f,
            };
        }
        else
        {
            hand[i]->bounds = 
            {
                calculatedPosition,
                220.0f,
                cardWidth - overlapWidth,
                100.0f,
            };
        }

        float scale = 1.0f + hand[i]->popAmount; 
        SDL_FRect drawPos = hand[i]->handPosition;
        drawPos.w *= scale;
        drawPos.h *= scale;
        drawPos.x -= (drawPos.w - hand[i]->handPosition.w) / 2;
        drawPos.y -= (drawPos.h - hand[i]->handPosition.h);


        if(hand[i]->selected)
        {
            hand[i]->bounds.y -= hand[i]->selectSpeed;
            drawPos.y -= (hand[i]->selectSpeed);
        }

        hand[i]->Draw(r, drawPos);

        handCount+=1;
    }

}

//Render Function to hold all render instances
void Hand::Render(SDL_Renderer *r)
{
   RenderHandArea(r);
   RenderHandCards(r);
}

Hand::~Hand()
{

}