#pragma once
#include "Card.h"
#include <vector>
#include <memory>
#include "Deck.h"
#include <cstdlib>
#include "Button.h"
#include <algorithm>
#include <map>

class Hand
{
private:
public:
    Deck *deck;
    float maxHandSize = 8.0f;
    int hoveredCardIndex;
    float maxPop = 0.1f;
    float maxSelectPosition = 50.0f;
    int selectedAmount = 0;

    bool discard = false;
    bool playHand = false;
    int handScore = 0;

    std::vector<std::unique_ptr<Card>> hand;
    std::vector<std::unique_ptr<Card>> selected;
    Hand();
    ~Hand();
    void print();
    int getScore();
    void updateHoverAnimation(double delta);
    void updateSelectAnimation(double delta);
    void Update(SDL_Renderer *r, double delta);
    bool checkHover(int mouseX, int mouseY);
    void checkSelected(int mouseX, int mouseY);
    void drawCards(SDL_Renderer *r, int drawSize);
    void Render(SDL_Renderer *r);
    void Init(SDL_Renderer *r, Deck *d);
    void RenderHandArea(SDL_Renderer *r);
    void RenderHandCards(SDL_Renderer *r);
    void discardCards();
    void getScoreCards();
    void calculateScore();

};
