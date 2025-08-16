#include "Hand.h"


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
        drawCards(r, maxHandSize - hand.size());
    }
}

//Draws cards based on amount of cards in hand
void Hand::drawCards(SDL_Renderer *r, int drawSize)
{
    for(int i = 0; i < drawSize; i++)
    {
        srand(getpid());
        int randomNum = rand() % deck->cards.size();
        hand.push_back(std::move(deck->cards[randomNum]));
        deck->Discard(randomNum);
    }
}

//prints current hand
void Hand::print()
{
    for(int i = 0; i < hand.size(); i++)
    {
        SDL_Log("Index: %d Rank: %d", i, hand[i]->cardRank);
    }
}

//Discards selected cards
void Hand::discardCards()
{

    //Removes selected cards from hand
    hand.erase(
        std::remove_if(hand.begin(), hand.end(), [&](std::unique_ptr<Card> &card) {
            if (card->selected) {
                selectedAmount -= 1;
                return true; // remove this card
            }
            return false;
        }),
        hand.end()
    );

    //SDL_Log("Hand Size: %d", hand.size());
}

//Creates the score for the selected cards
void Hand::getScoreCards()
{
    selected.clear();
    auto it = hand.begin();
    while (it != hand.end())
    {
        if ((*it)->selected)
        {
            selected.push_back(std::move(*it));
            it = hand.erase(it);
            selectedAmount -=1;
        }
        else
        {
            ++it;
        }
    }
}

//Scoring Logic
void Hand::calculateScore()
{
    std::map<int, int> rankCount;
    std::map<int, int> suitCount;
    std::vector<int> ranks;

    for (auto &card : selected) {
        rankCount[card->cardRank]++;
        suitCount[card->cardSuit]++;
        ranks.push_back(card->cardRank);
    }

    // Sort ranks for straight checking
    std::sort(ranks.begin(), ranks.end());
    
    // Handle Ace high by adding 14 if Ace is present
    if (std::find(ranks.begin(), ranks.end(), 1) != ranks.end()) {
        ranks.push_back(14);
    }

    // ---- Now check combinations ----
    bool flush = false;
    for (auto &s : suitCount) {
        if (s.second >= 5) flush = true;
    }

    bool straight = false;
    int consecutive = 1;
    for (size_t i = 1; i < ranks.size(); i++) {
        if (ranks[i] == ranks[i-1] + 1) {
            consecutive++;
            if (consecutive >= 5) straight = true;
        } else if (ranks[i] != ranks[i-1]) {
            consecutive = 1;
        }
    }

    // Check multiples
    int pairs = 0, three = 0, four = 0;
    for (auto &r : rankCount) {
        if (r.second == 2) pairs++;
        if (r.second == 3) three++;
        if (r.second == 4) four++;
    }

    // ---- Decide Hand Strength ----
    if (straight && flush) handScore = 9;
    if (four)  handScore = 8;
    if (three && pairs) handScore = 7;
    if (flush) handScore = 6;
    if (straight) handScore = 5;
    if (three) handScore = 4;
    if (pairs >= 2) handScore = 3;
    if (pairs == 1) handScore = 2;
    
    if(handScore == 0)
    {
        handScore = 1;
    }
}

//Gets the hand score
int Hand::getScore()
{
    return handScore;
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
            //SDL_Log("%d", hand[hoveredCardIndex]->cardRank);
            selectedAmount +=1;
        }
    }
    //SDL_Log("\nselected_amount in check: %d\n", selectedAmount);
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
void Hand::Update(SDL_Renderer *r ,double delta)
{
    if(discard)
    {
        discardCards();
        if(deck->cards.size() < (maxHandSize - hand.size()))
        {
            drawCards(r, deck->cards.size());
        }
        else
        {
            drawCards(r, maxHandSize - hand.size());
        }
        discard = false;
    }

    if(playHand)
    {
        getScoreCards();
        calculateScore();
        if(deck->cards.size() < (maxHandSize - hand.size()))
        {
            drawCards(r, deck->cards.size());
        }
        else
        {
            drawCards(r, maxHandSize - hand.size());
        }
        playHand = false;
    }

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