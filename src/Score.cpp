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

void Score::updateScoreText(SDL_Renderer *r, int fontSize, SDL_Color tColor)
{
    textColor = {
            tColor.r,
            tColor.g,
            tColor.b,
            tColor.a
    };

    if(score != lastScore)
    {
        if(textTexture)
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;

        font = TTF_OpenFont("../assets/Fonts/arial.ttf", fontSize);
        if(!font)
        {
            SDL_Log("font did not load properly");
        }

        std::string scoreStr = std::to_string(score);

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), strlen(scoreStr.c_str()), textColor);
        
        if (!textSurface) {
            SDL_Log("unable to render texture surface");
            return;
        }

        textTexture = SDL_CreateTextureFromSurface(r, textSurface);
        if(!textTexture)
        {
            SDL_Log("couldnt load score text texture");
            return;
        }

        SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);
        SDL_DestroySurface(textSurface);

        SDL_PropertiesID textTextureProperties;
        textTextureProperties = SDL_GetTextureProperties(textTexture);

        textW = SDL_GetNumberProperty(textTextureProperties, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
        textH = SDL_GetNumberProperty(textTextureProperties, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);

        textRect = {((scoreRect.x + (scoreRect.w/2)) - textW/2), ((scoreRect.y + (scoreRect.h/2)) - textH/2), textW, textH};
        tempTextRect = textRect;
        SDL_DestroySurface(textSurface);
    }
}

bool Score::Render(SDL_Renderer *r)
{

    if(!SDL_RenderTexture(r, texture, &srcRect, &scoreRect))
    {
        SDL_Log("could not render score texture");
        return false;
    }
    if(textTexture)
    {
        if(!SDL_RenderTexture(r, textTexture, nullptr, &textRect))
        {
            SDL_Log("Couldnt render textTexture for score");
            return false;
        }
    }
    return true;
}