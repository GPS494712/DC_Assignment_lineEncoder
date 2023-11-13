#include <iostream>
#include <vector>
#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int scale = 40;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("Line Encoder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set renderer draw color
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    return true;
}

void closeSDL()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void drawGrid()
{
    // Set draw color for the grid lines
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);

    // Draw horizontal lines
    for (int i = 0; i <= SCREEN_HEIGHT; i += scale)
    {
        SDL_RenderDrawLine(gRenderer, 0, i, 800, i);
    }

    // Draw vertical lines
    for (int i = 0; i <= SCREEN_WIDTH; i += scale)
    {
        SDL_RenderDrawLine(gRenderer, i, 0, i, 600);
    }
}

// draw square wave for this grid cartitian plane amplqitude 1

void Nrz_l(int *test, int size)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    int xx = 0, yy = 260;
    for (int i = 0; i < size - 1; i++)
    {
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);

        if (test[i] == 0)
        {
            SDL_RenderDrawLine(gRenderer, xx, 260, (xx) + scale, 260);
            xx = xx + scale;
        }
        else
        {
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx + scale), 300);
            xx = xx + scale;
        }

        if (test[i + 1] != test[i])
        {
            SDL_RenderDrawLine(gRenderer, (xx), 260, (xx), 300);
        }
    }

    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), 300, (xx + scale), 300);
    }
    else
    {
        SDL_RenderDrawLine(gRenderer, xx, 260, (xx) + scale, 260);
    }
}

void Nrz_i(int *test, int size)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    int xx = 0, yy = 260;
    bool change = false;
    // std::vector<int>y(260,300);
    int y;
    for (int i = 0; i < size - 1; i++)
    {
        y = change ? 320 : 280;
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);

        SDL_RenderDrawLine(gRenderer, xx, y, (xx) + scale, y);
        xx = xx + scale;

        if (test[i + 1] == 1)
        {
            SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
            change = !change;
        }
    }
    y = change ? 320 : 280;
    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
    }
    else
    {
        SDL_RenderDrawLine(gRenderer, xx, y, (xx) + scale, y);
    }
}

void manchaster(int *test, int size)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    int xx = 0, yy = 260;
    for (int i = 0; i < size - 1; i++)
    {
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);
        if (test[i] == 0)
        {
            SDL_RenderDrawLine(gRenderer, xx, 280, (xx) + (scale / 2), 280);
            xx = xx + (scale / 2);
            SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
            SDL_RenderDrawLine(gRenderer, (xx), 320, (xx + (scale / 2)), 320);
            xx = xx + (scale / 2);
        }
        else
        {
            SDL_RenderDrawLine(gRenderer, (xx), 320, (xx + (scale / 2)), 320);
            xx = xx + (scale / 2);
            SDL_RenderDrawLine(gRenderer, (xx), 320, (xx), 280);
            SDL_RenderDrawLine(gRenderer, (xx), 280, (xx + (scale / 2)), 280);
            xx = xx + (scale / 2);
        }

        if (test[i + 1] == test[i])
        {
            SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
        }
    }

    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), 320, (xx + (scale / 2)), 320);
        xx = xx + (scale / 2);
        SDL_RenderDrawLine(gRenderer, (xx), 320, (xx), 280);
        SDL_RenderDrawLine(gRenderer, (xx), 280, (xx + (scale / 2)), 280);
    }
    else
    {
        SDL_RenderDrawLine(gRenderer, xx, 280, (xx) + (scale / 2), 280);
        xx = xx + (scale / 2);
        SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
        SDL_RenderDrawLine(gRenderer, (xx), 320, (xx + (scale / 2)), 320);
    }
}

void d_manchester(int *test, int size)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    int xx = 0, yy = 260;
    bool change = false;
    // std::vector<int>y(260,300);
    int y;
    for (int i = 0; i < size - 1; i++)
    {
        y = change ? 320 : 280;
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);

        SDL_RenderDrawLine(gRenderer, xx, y, (xx) + (scale/2), y);
        xx = xx + (scale / 2);
        SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
        if(y == 320) {y = 280;}
        else {y = 320;}
        SDL_RenderDrawLine(gRenderer, (xx), y, (xx + (scale / 2)), y);
        xx = xx + (scale / 2);

        if (test[i + 1] == 0)
        {
            SDL_RenderDrawLine(gRenderer, (xx), 280, (xx), 320);
          
        }
        else{
            change = !change;
        }
    }
    y = change ? 320 : 280;
    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
    }
    else
    {
        SDL_RenderDrawLine(gRenderer, xx, y, (xx) + scale, y);
    }
}


int main(int argc, char *args[])
{
    int n;
    std::cout << "Enter the number of Bits: ";
    std::cin >> n;
    std::cout << "Enter the Bits : ";
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    if (!initSDL())
    {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    int xOffset = 0;

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        // Draw the centered Cartesian plane grid
        drawGrid();
        // Nrz_l(arr, n);
        // Update the screen
        // Nrz_i(arr, n);
        // manchaster(arr, n);
        d_manchester(arr, n);

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();

    return 0;
}
