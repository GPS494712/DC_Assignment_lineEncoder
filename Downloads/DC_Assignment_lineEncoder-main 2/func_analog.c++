#include <iostream>
#include <vector>

#include <string>
#include <unordered_map>
#include <cmath>
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"


// Function to generate a sine wave
double sine_wave(double frequency, double amplitude, double time)
{
    return amplitude * sin(-2 * PI * frequency * time);
}

// Function to generate a cosine wave
double cosine_wave(double frequency, double amplitude, double time)
{
    return -1 * amplitude * cos(2 * PI * frequency * time);
}

// Function to generate a triangle wave
double triangle_wave(double frequency, double amplitude, double time)
{
    return (2 / PI) * asin(sin(-2 * PI * frequency * time)) * amplitude;
}



std::string A2D(std::unordered_map<int, std ::string> map, std::vector<int> arr)
{
    // std::cout << arr.size() << std::endl;
    std::string str;
    for (int i = 0; i < arr.size(); i++)
    {
        str += map[arr[i]];
    }
    // std::cout << str << std::endl;
    return str;
}

void Quantization(int y, std::vector<int> &arr)
{
    y = y / 10;
    y = round(y) * 10;
    arr.push_back(y);
    // std::cout << y << std::endl;
}

std:: string SamplingWave(std::unordered_map<int, std ::string> map, std::string frequency_str, std::string amplitude_str)
{
    std::vector<int> arr;
    int frequency_ = stoi(frequency_str);
    int amplitude_ = stoi(amplitude_str);
    for (float i = SAMPLE_RATE; i < 8; i += SAMPLE_RATE)
    {
        double y = sine_wave(frequency_, amplitude_, i);
        if (y > 5 || y < -5)
        {
            Quantization(y, arr);
        }
    }
    std :: string s1= A2D(map, arr);
    return s1;
}


// void render_text(SDL_Renderer *renderer, const char *text, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
// {
//     TTF_Font *font = TTF_OpenFont("./Roboto-Regular.ttf", 24);
//     if (!font)
//     {
//         std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
//         return;
//     }

//     SDL_Color color = {r, g, b, a};
//     SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

//     SDL_Rect destRect = {x, y, surface->w, surface->h};
//     SDL_RenderCopy(renderer, texture, nullptr, &destRect);

//     SDL_FreeSurface(surface);
//     SDL_DestroyTexture(texture);
//     TTF_CloseFont(font);
// }

// int main()
// {

    // // Initialize SDL
    // if (SDL_Init(SDL_INIT_VIDEO) < 0)
    // {
    //     std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    //     return 1;
    // }

    // // Initialize SDL_ttf
    // if (TTF_Init() == -1)
    // {
    //     std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
    //     return 1;
    // }

    // // Create window
    // SDL_Window *window = SDL_CreateWindow("Waveforms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_A, SCREEN_HEIGHT_A, SDL_WINDOW_SHOWN);
    // if (window == nullptr)
    // {
    //     std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // // Create renderer
    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // if (renderer == nullptr)
    // {
    //     std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window);
    //     SDL_Quit();
    //     return 1;
    // }
    
    // // Main loop
    // bool quit = false;
    // SDL_Event e;

    // while (!quit)
    // {
    //     // Handle events on queue
    //     while (SDL_PollEvent(&e) != 0)
    //     {
    //         if (e.type == SDL_QUIT)
    //         {
    //             quit = true;
    //         }
    //     }

    //     // Clear the renderer
    //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //     SDL_RenderClear(renderer);

    //     // Draw grid
    //     SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    //     draw_grid(renderer);

    //     // Draw axes labels
    //     // draw_axes_labels(renderer);

    //     // Draw X and Y axes lines
    //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //     SDL_RenderDrawLine(renderer, SCREEN_WIDTH_A / 2, 0, SCREEN_WIDTH_A / 2, SCREEN_HEIGHT_A);  // Y-axis
    //     SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT_A / 2, SCREEN_WIDTH_A, SCREEN_HEIGHT_A / 2); // X-axis

    //     // std::vector<int> arr;
    //     // for(int i = SAMPLE_RATE; i < SCREEN_WIDTH_A; i += SAMPLE_RATE)
    //     // {
    //     //     double y = sine_wave(1, 50, i);
    //     //     // Quantization(y, arr);
    //     //     std:: cout << y << "                                                  " << std::endl;

    //     // }
    //     // double y = sine_wave(1, 50, SAMPLE_RATE);
    //     // std:: cout << y << "                                                  " << std::endl;
    //     // SamplingWave();

    //     //  // blue for custom wave
    //     // draw_continuous_wave(renderer, custom_wave, 2, 50, 3, 50, red);

    //     Uint8 red[4] = {255, 0, 0, 255}; // red for sine wave
    //     // call sine_wave function here
    //     

    //     // Uint8 green[4] = {0, 255, 0, 255}; // green for cosine wave
    //     // // call cosine_wave function here
    //     // draw_continuous_wave(renderer, cosine_wave, 2, 50, green);

    //     // Uint8 blue[4] = {0, 0, 255, 255}; // blue for triangle wave
    //     // // call triangle_wave function here
    //     // draw_continuous_wave(renderer, triangle_wave, 2, 50, blue);

    //     // Update the renderer
    //     SDL_RenderPresent(renderer);
    // }

    // // Clean up
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    // return 0;
// }
