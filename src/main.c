#include <stdio.h>
#include <stdbool.h>

#include "SDL2/SDL_main.h"
#include "SDL2/SDL.h"
#include "Player.h"

bool bIsGameRunning = false;
SDL_Window* windowPtr = NULL;
SDL_Renderer* rendererPtr = NULL;
int32_t lastFrameMilliseconds = 0;
Player myPlayer = { 300, 300, 8, 8 };

bool InitializeWindow(int32_t inWindowWith, int32_t inWindowHeight);
void ProcessInput();
void Update();
void Render();
void MainLoop();
void ReleaseMemory();

void DrawPlayer();


int main(int argc, char* argv[])
{
    bIsGameRunning = InitializeWindow(1024, 512);
    MainLoop();
    ReleaseMemory();
}

bool InitializeWindow(int32_t inWindowWith, int32_t inWindowHeight)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not be initialized: %s\n", SDL_GetError());
        return false;
    }

    windowPtr = SDL_CreateWindow(
        "RayCasterProject",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        inWindowWith,
        inWindowHeight,
        SDL_WINDOW_SHOWN);
    if (windowPtr == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        return false;
    }

    rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rendererPtr == NULL)
    {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        return false;
    }

    // SDL_SetWindowFullscreen(p_window, 0);
    return true;
}

void ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            bIsGameRunning = false;
            break;

        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                bIsGameRunning = false;
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}

void Update()
{
    // Delay the update function to match with the Frame Target Time
    const uint8_t FPS = 60;
    const uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

    int32_t timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - lastFrameMilliseconds);
    if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // float deltaTime = (SDL_GetTicks() - lastFrameMilliseconds) / 1000.0f;
    lastFrameMilliseconds = SDL_GetTicks();
}
void Render()
{
    // Set a light gray background
    SDL_SetRenderDrawColor(rendererPtr, 80, 80, 80, 255);
    SDL_RenderClear(rendererPtr);
    DrawPlayer();
    SDL_RenderPresent(rendererPtr);
}

void MainLoop()
{
    while (bIsGameRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void ReleaseMemory()
{
    SDL_DestroyRenderer(rendererPtr);
    SDL_DestroyWindow(windowPtr);
    SDL_Quit();
}

void DrawPlayer()
{
    // Display a basic yellow rectangle player
    SDL_Rect ballRectangle = { myPlayer.m_positionX, myPlayer.m_positionY, myPlayer.m_width, myPlayer.m_height };
    SDL_SetRenderDrawColor(rendererPtr, 255, 255, 0, 255);
    SDL_RenderFillRect(rendererPtr, &ballRectangle);
}
