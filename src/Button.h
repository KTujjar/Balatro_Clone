#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_render.h>

class Button
{
private:
    
public:

    //text in button
    const char *buttonText;
    SDL_Color textColor;
    float textW, textH;
    TTF_Font *font;
    SDL_FRect textRect;
    float fontSize;
    SDL_Texture *textTexture = nullptr;

    //Texture for button if asset
    SDL_Texture *texture = nullptr;
    SDL_FRect textureRect;


    //button position and size
    SDL_FRect buttonRect;
    SDL_Color buttonColor;

    //Initializes Button From: renderer | filename(nullptr if no texture) | text for button(nullptr for no text) | font size of text | source rect(emtpyrect if no texture) | destination rect | color of button(empty rect if texture) | color of text(empty rect if no text) 
    void Init(SDL_Renderer *r, const char *filename, const char *text, float fSize, SDL_FRect srcRect, SDL_FRect rect, SDL_Color Color, SDL_Color tColor);
    
    
    void createButton(SDL_Renderer *r);
    
    
    bool Render(SDL_Renderer *r);
    
    Button();
    ~Button();
};

