#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "SDL2/SDL_main.h"
#include "SDL2/SDL.h"
#include "Player.h"


/////////////////////////////////////////////////////////////////
// MAIN APP MANAGEMENT 
/////////////////////////////////////////////////////////////////
bool bIsGameRunning = false;
SDL_Window* windowPtr = NULL;
SDL_Renderer* rendererPtr = NULL;
int32_t lastFrameMilliseconds = 0;

bool InitializeWindow(int32_t inWindowWith, int32_t inWindowHeight);
void ProcessInput();
void Update();
void Render();
void MainLoop();
void ReleaseMemory();


/////////////////////////////////////////////////////////////////
// PLAYER - MAP MANAGEMENT
/////////////////////////////////////////////////////////////////
#define PI 3.141592
Player myPlayer = { 300, 300, 8, 8, 0 };
#define MAP_TOTAL_COLUMNS 8
#define MAP_TOTAL_ROWS 8
#define MAP_CELL_SIZE 64
int8_t map2D[] =
{
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1
};

void DrawPlayer();
void Draw2DMap();

/////////////////////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////////////////////
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

            case SDLK_w:
                myPlayer.m_positionX += 5 * cos(myPlayer.m_angleInRadians);
                myPlayer.m_positionY += 5 * sin(myPlayer.m_angleInRadians);
                break;

            case SDLK_s:
                myPlayer.m_positionX -= 5 * cos(myPlayer.m_angleInRadians);
                myPlayer.m_positionY -= 5 * sin(myPlayer.m_angleInRadians);
                break;

            case SDLK_a:
                myPlayer.m_angleInRadians -= 0.1;
                if (myPlayer.m_angleInRadians > 2 * PI) { myPlayer.m_angleInRadians -= 2 * PI; }
                break;
            
            case SDLK_d:
                myPlayer.m_angleInRadians += 0.1;
                if (myPlayer.m_angleInRadians < 0) { myPlayer.m_angleInRadians += 2 * PI; }
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
    Draw2DMap();
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
    SDL_SetRenderDrawColor(rendererPtr, 255, 255, 0, 255);
    
    SDL_Rect ballRectangle = { (int)roundf(myPlayer.m_positionX), (int)roundf(myPlayer.m_positionY), myPlayer.m_width, myPlayer.m_height };
    SDL_RenderFillRect(rendererPtr, &ballRectangle);

    int32_t playerCenterX = (int)roundf(myPlayer.m_positionX) + myPlayer.m_width / 2;
    int32_t playerCenterY = (int)roundf(myPlayer.m_positionY) + myPlayer.m_width / 2;
    SDL_RenderDrawLine(rendererPtr,
                        playerCenterX,
                        playerCenterY,
                        (int)roundf(playerCenterX + 20.f * cos(myPlayer.m_angleInRadians)),
                        (int)roundf(playerCenterY + 20.f * sin(myPlayer.m_angleInRadians)));

}

void Draw2DMap()
{
    for (size_t y = 0; y < MAP_TOTAL_ROWS; y++)
    {
        for (size_t x = 0; x < MAP_TOTAL_COLUMNS; x++)
        {
            if (map2D[y * MAP_TOTAL_COLUMNS + x] == 0)
            {
                SDL_SetRenderDrawColor(rendererPtr, 0, 0, 0, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(rendererPtr, 255, 255, 255, 255);
            }

            SDL_Rect wallRectangle = { x * MAP_CELL_SIZE + 1, y * MAP_CELL_SIZE + 1 , MAP_CELL_SIZE - 2, MAP_CELL_SIZE - 2};
            SDL_RenderFillRect(rendererPtr, &wallRectangle);
        }
    }
}
