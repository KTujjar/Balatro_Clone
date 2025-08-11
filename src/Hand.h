#pragma once
#include "Card.h"
#include <vector>
#include <memory>

class Hand
{
private:
public:
    float maxHandSize = 20.f;
    static int handCount;
    std::vector<std::unique_ptr<Card>> hand;
    Hand();
    ~Hand();
    void Draw(SDL_Renderer *r, int drawSize);
    void Render(SDL_Renderer *r);
    void Init(SDL_Renderer *r);
    void RenderHandArea(SDL_Renderer *r);
    void RenderHandCards(SDL_Renderer *r);

};
