#include <iostream>
#include <vector>
#include "SDL2/SDL.h"

void Nrz_l(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
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

void Nrz_i(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
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

void manchaster(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
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

void d_manchester(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
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

void AMI(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    bool change = false;
    int xx = 0, yy = 260;
    int y = change? 320 : 280;
    for (int i = 0; i < size - 1; i++)
    {
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);
        int y = change? 320 : 280;


        if (test[i] == 0)
        {
            SDL_RenderDrawLine(gRenderer, xx, 300, (xx) + scale, 300);
            xx = xx + scale;
        }
        else
        {
            SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
            xx = xx + scale;
            change = !change;
        }

        if (test[i + 1] == 1)
        {
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        }

        if(test[i] == 1){
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        }
    }

    y = change? 320 : 280;

    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
        xx = xx + scale;
        SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
    }
    else
    {
        SDL_RenderDrawLine(gRenderer, xx, 300, (xx) + scale, 300);
    }
}

void scramble(int *test, int size, SDL_Renderer* gRenderer,int scale)
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    bool change = false;
    int xx = 0, yy = 260;
    int y = change? 320 : 280;
    for (int i = 0; i < size - 1; i++)
    {
        // SDL_RenderDrawLine(gRenderer, (i*2), 260, (i*2), 300);
        // SDL_RenderDrawLine(gRenderer, i*2, 260, (i*2+scale), 260);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 260, scale+(i*2), 300);
        // SDL_RenderDrawLine(gRenderer, scale+(i*2), 300, scale+(i*2+scale), 300);
        int y = change? 320 : 280;

        // if(test[i] == 2){
        // //    test[i] = 1;
        // }

        if (test[i] == 0)
        {
            SDL_RenderDrawLine(gRenderer, xx, 300, (xx) + scale, 300);
            xx = xx + scale;
        }
        else
        {
            SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
            xx = xx + scale;
            change = !change;
        }

        if(test[i] == 1){
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        }
        if(test[i] == 2){
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        }

        if (test[i + 1] == 1)
        {
            y = change? 320 : 280;
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        }
        if(test[i + 1] == 2){
            change = !change;
            y = change? 320 : 280;
            SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
        } 

    }

    y = change? 320 : 280;

    if (test[size - 1] == 1)
    {
        SDL_RenderDrawLine(gRenderer, (xx), y, (xx + scale), y);
        xx = xx + scale;
        SDL_RenderDrawLine(gRenderer, (xx), 300, (xx), y);
    }
    else if(test[size - 1] == 0)
    {
        SDL_RenderDrawLine(gRenderer, xx, 300, (xx) + scale, 300);
    }
    else{
        SDL_RenderDrawLine(gRenderer, xx, y, (xx) + scale, y);
    }
}
