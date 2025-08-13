#include "Button.h"


Button::Button()
{

}

Button::~Button()
{
    TTF_CloseFont(font);
}

//takes in text for center of button, buttonRect, and the rgb for the button
void Button::Init(SDL_Renderer *r, const char *text, float fSize, SDL_FRect rect, SDL_Color Color, SDL_Color tColor)
{
    buttonText = text;
    buttonRect = rect;
    fontSize = fSize;

    buttonColor = {
        Color.r,
        Color.g,
        Color.b,
        Color.a
    };

    textColor = {
        tColor.r,
        tColor.g,
        tColor.b,
        tColor.a
    };

    font = TTF_OpenFont("../assets/Fonts/arial.ttf", fontSize);
    if(!font)
    {
        SDL_Log("font did not load properly");
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText, strlen(buttonText), textColor);

    if (!textSurface) {
        SDL_Log("unable to render texture surface");
    }

    textTexture = SDL_CreateTextureFromSurface(r, textSurface);
    SDL_SetTextureScaleMode(textTexture, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(textSurface);

    SDL_PropertiesID textTextureProperties;
    textTextureProperties = SDL_GetTextureProperties(textTexture);

    textW = SDL_GetNumberProperty(textTextureProperties, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
    textH = SDL_GetNumberProperty(textTextureProperties, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);

    textRect = {((buttonRect.x + (buttonRect.w/2)) - textW/2), ((buttonRect.y + (buttonRect.h/2)) - textH/2), textW, textH};
}

bool Button::Render(SDL_Renderer *r)
{
    if(!SDL_SetRenderDrawColor(r, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a))
    {
        SDL_Log("failed to load button Color");
        return false;
    }
    if(!SDL_RenderFillRect(r, &buttonRect))
    {
        SDL_Log("Failed to render button");
        return false;
    }
    if(!SDL_SetRenderDrawColor(r, textColor.r, textColor.g, textColor.b, textColor.a))
    {
        SDL_Log("failed to load text Color");
        return false;
    }
    if(!SDL_RenderTexture(r, textTexture, nullptr, &textRect))
    {
        SDL_Log("Failed to load Text");
        return false;
    }

    return true;
}
