#pragma once
#include "Card.h"
#include <vector>
#include <memory>
#include "Deck.h"
#include <cstdlib>

class Hand
{
private:
public:
    Deck *deck;
    float maxHandSize = 8.0f;
    int hoveredCardIndex;
    static int handCount;
    float maxPop = 0.1f;
    float maxSelectPosition = 50.0f;
    int selectedAmount = 0;
    std::vector<std::unique_ptr<Card>> hand;
    Hand();
    ~Hand();
    void updateHoverAnimation(double delta);
    void updateSelectAnimation(double delta);
    void Update(double delta);
    bool checkHover(int mouseX, int mouseY);
    void checkSelected(int mouseX, int mouseY);
    void Draw(SDL_Renderer *r, int drawSize);
    void Render(SDL_Renderer *r);
    void Init(SDL_Renderer *r, Deck *d);
    void RenderHandArea(SDL_Renderer *r);
    void RenderHandCards(SDL_Renderer *r);

};
