#include "Score.h"


Score::Score()
{

}

Score::~Score()
{
    
}

void Score::Init(SDL_Renderer *r)
{
    texture = IMG_LoadTexture(r, "../assets/Buttons/Score.png");
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    scoreRect = {
        (float)(Global::windowWidth/2) - 150/2,
        10.0f,
        150.0f,
        50.0f
    };

    srcRect = {
        0.0f,
        0.0f,
        150.0f,
        50.0f
    };

}

bool Score::Render(SDL_Renderer *r)
{

    if(!SDL_RenderTexture(r, texture, &srcRect, &scoreRect))
    {
        SDL_Log("could not render score texture");
        return false;
    }
    return true;
}