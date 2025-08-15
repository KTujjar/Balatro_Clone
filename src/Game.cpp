#include "Game.h"

Game::Game()
{
    renderWindow();
}

//Loads Assets once before main game loop
void Game::loadTextures()
{
    deck.Init(renderer, "../assets/Cards/Cards.png");
    hand.Init(renderer, &deck);
    playButton.Init(renderer, "../assets/Buttons/PlayHandAnimSheet.png", true, "Play Hand", 18.0f, {0, 0, 100, 50}, {10, 230, 100, 50}, {30, 144, 255, 255}, {255, 255, 255, 255});
    discardButton.Init(renderer, "../assets/Buttons/DiscardAnimSheet.png", true, "Discard", 18.0f, {0, 0, 100, 50}, {10, 285, 100, 50}, {30, 144, 255, 255}, {255, 255, 255, 255});
    score.Init(renderer);
}

//Game Loop
void Game::run()
{
    loadTextures();
    SDL_ShowWindow(window);

    Uint64 last = SDL_GetPerformanceCounter();

    while(window != NULL)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double dt = double(now - last) / SDL_GetPerformanceFrequency();
        last = now;

        processEvents();
        update(dt);
        render();
        updateFPS(dt);
    }
}

void Game::updateFPS(double dt)
{
    double fps = 1.0 / dt;

    //SDL_Log("FPS: %.2f", fps);
}

//Handles updating whats drawin on screen
void Game::update(double delta)
{
    hand.Update(delta);
}

//Handles drawing to screen
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderLogicalPresentation(renderer, Global::windowWidth, Global::windowHeight, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE); //scales renderer with window

    playButton.Render(renderer);
    discardButton.Render(renderer);
    deck.Render(renderer);
    hand.Render(renderer);
    score.Render(renderer);

    SDL_SetRenderDrawColor(renderer, 39, 73, 56, 255);
    SDL_RenderPresent(renderer);
}

//Frees all allocated memory for game after close
Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);



    TTF_Quit();
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


        handleMouseEvent(e);
        handleWindowEvent(e);
    }
}

void Game::handleMouseEvent(const SDL_Event &e)
{
    int mx = e.motion.x;
    int my = e.motion.y;

    if(flags & SDL_WINDOW_FULLSCREEN)
    {
        mx = e.motion.x / 3;
        my = e.motion.y / 3;
    }

    if(e.type == SDL_EVENT_MOUSE_MOTION) {

        flags = SDL_GetWindowFlags(window);
        
        hand.checkHover(mx, my); // store which card is hovered
        playButton.checkHover(mx,my);
        discardButton.checkHover(mx,my);
    }
    
    if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            hand.checkSelected(mx,my);
            playButton.checkPressed(mx,my,2);
            discardButton.checkPressed(mx,my,2);
        }
    }

    if(e.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            playButton.checkReleased(mx, my);
            discardButton.checkReleased(mx,my);
        }
    }
}

void Game::renderWindow()
{
    //Render Window
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if(!TTF_Init())
    {
        SDL_Log("TTF not Initializing");
    }
    
        
    window = SDL_CreateWindow("Balatro Clone", Global::windowWidth, Global::windowHeight, SDL_EVENT_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, NULL);

    if (!window || !renderer) {
        SDL_Log("Window or Renderer creation failed: %s", SDL_GetError());
        return;
    }

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Failed to enable VSync: %s", SDL_GetError());
    }
    
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
        
}

//Handles Resizing Window
void Game::handleWindowEvent(const SDL_Event &e)
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
