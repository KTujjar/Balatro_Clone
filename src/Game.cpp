#include "Game.h"

Game::Game()
{

    //Render Window
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        if(!SDL_CreateWindowAndRenderer("Balatro Clone", Global::windowWidth, Global::windowHeight, SDL_EVENT_WINDOW_SHOWN, &window, &renderer))
        {
            SDL_Log( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Get pixel format of surface
            details = SDL_GetPixelFormatDetails( screenSurface->format );

            //Fill the surface white
            SDL_FillSurfaceRect( screenSurface, NULL, SDL_MapRGB( details, NULL, 0xFF, 0xFF, 0xFF ));
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            SDL_SetWindowFullscreen(window, SDL_WINDOW_BORDERLESS);
        }
    }
}

//Loads Assets once before main game loop
void Game::loadTextures()
{
    hand.Init(renderer);
}

//Game Loop
void Game::run()
{
    Uint64 last = SDL_GetPerformanceCounter();

    loadTextures();
    while(window != NULL)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double dt = double(now - last) / SDL_GetPerformanceFrequency();
        last = now;

        processEvents();
        update(dt);
        render();
    }
}

//Handles updating whats drawin on screen
void Game::update(double delta)
{
}

//Handles drawing to screen
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 39, 73, 56, 255); // Clear to black
    SDL_RenderClear(renderer);
    SDL_SetRenderVSync(renderer, 1);
    SDL_SetRenderLogicalPresentation(renderer, Global::windowWidth, Global::windowHeight, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE); //scales renderer with window


    hand.Render(renderer);
    //Card card(renderer, "../assets/Cards/Ace_Heart.png");
    //Card card(renderer, "../assets/Cards/Ace_Heart.png");


    SDL_RenderPresent(renderer);
}

//Frees all allocated memory for game after close
Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);





    SDL_Quit();
}

//Keeps game running 
void Game::processEvents()
{
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_EVENT_QUIT)
        {
            window = NULL;
            break;
        }
        handleEvent(e);
    }
}

//Handles Resizing Window
void Game::handleEvent(const SDL_Event &e)
{
    if (e.type == SDL_EVENT_KEY_DOWN) {
        if (e.key.scancode == SDL_SCANCODE_F11) 
        {
            flags = SDL_GetWindowFlags(window);
            if(flags & SDL_WINDOW_FULLSCREEN)
                SDL_SetWindowFullscreen(window, 0);
            else
                SDL_SetWindowFullscreen(window, SDL_WINDOW_BORDERLESS);
        }
    }   
}
