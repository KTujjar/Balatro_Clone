
#pragma once
#include "Card.h"
#include <vector>
#include <memory>

class Deck
{
private:

public:
    std::vector<std::unique_ptr<Card>> deck;
    Deck();
    ~Deck();
};

