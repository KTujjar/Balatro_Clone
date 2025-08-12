#pragma once
#include "Card.h"
#include <vector>
#include <memory>

class Hand
{
private:
public:
    float maxHandSize = 8.0f;
    int hoveredCardIndex;
    static int handCount;
    float maxPop = 0.5f;
    std::vector<std::unique_ptr<Card>> hand;
    Hand();
    ~Hand();
    void updateHoverAnimation(double delta);
    void checkHover(int mouseX, int mouseY);
    void Draw(SDL_Renderer *r, int drawSize);
    void Render(SDL_Renderer *r);
    void Init(SDL_Renderer *r);
    void RenderHandArea(SDL_Renderer *r);
    void RenderHandCards(SDL_Renderer *r);

};
