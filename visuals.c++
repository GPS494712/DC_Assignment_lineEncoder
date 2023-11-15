#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "constants.h"
#include "func_analog.c++"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

std::string userInput = "";
std::string userFreqInput = "1";
std::string userAmpInput = "50";
bool selectedInputFA = false;

TTF_Font *font;
SDL_Color textColor = {0, 0, 255, 255};

SDL_Rect inputRect = {(100), 0, INPUT_WIDTH, INPUT_HEIGHT};

SDL_Rect buttonRect = {885, 550, BUTTON_WIDTH, BUTTON_HEIGHT};

SDL_Rect freqRect = {800, 500, 40, 40};
SDL_Rect ampRect = {850, 500, 40, 40};

void renderMenu_digital()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    // SDL_RenderDrawRect(gRenderer, &menuRect);

    if (isMenuVisible)
    {
        for (int i = 0; i < numMenuItems; i++)
        {
            SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);
            SDL_Rect itemRect = {800, 40 + i * MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
            SDL_RenderFillRect(gRenderer, &itemRect);

            // Render text for the item using SDL_ttf
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuItems[i], {0, 0, 0, 255});
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            SDL_Rect textRect = {800, 45 + i * MENU_HEIGHT, textSurface->w, textSurface->h};
            SDL_RenderCopy(gRenderer, textTexture, nullptr, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            if (selectedMenuItem == menuItems[i])
            {
                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
            }
        }
    }
}

void renderMenu_analog()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_Rect menuRect = {800, 200, MENU_WIDTH, MENU_HEIGHT};
    // SDL_RenderFillRect(gRenderer, &menuRect);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    // SDL_RenderDrawRect(gRenderer, &menuRect);

    if (isMenuVisible)
    {
        for (int i = 0; i < numMenuItemsAnalog; i++)
        {
            SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);
            SDL_Rect itemRect = {800, 40 + i * MENU_HEIGHT, MENU_WIDTH, MENU_HEIGHT};
            SDL_RenderFillRect(gRenderer, &itemRect);

            // Render text for the item using SDL_ttf
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuItemsAnalog[i], {0, 0, 0, 255});
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            SDL_Rect textRect = {800, 45 + i * MENU_HEIGHT, textSurface->w, textSurface->h};
            SDL_RenderCopy(gRenderer, textTexture, nullptr, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            if (selectedMenuItem == menuItemsAnalog[i])
            {
                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
            }
        }
    }
}

void renderComboBox_digital()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_Rect boxRect = {800, 10, MAIN_BOX_WIDTH, MAIN_BOX_HEIGHT};
    SDL_RenderFillRect(gRenderer, &boxRect);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &boxRect);

    if (selectedMenuItem)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, selectedMenuItem, {255, 255, 255, 255});
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect textRect = {805, 16, textSurface->w, textSurface->h};
        SDL_RenderCopy(gRenderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void renderComboBox_analog()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_Rect boxRect = {800, 10, MAIN_BOX_WIDTH, MAIN_BOX_HEIGHT};
    SDL_RenderFillRect(gRenderer, &boxRect);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(gRenderer, &boxRect);

    if (selectedMenuItem)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, selectedMenuItem, {255, 255, 255, 255});
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        SDL_Rect textRect = {805, 16, textSurface->w, textSurface->h};
        SDL_RenderCopy(gRenderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void renderForm_frequency()
{
    // Render input field
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &freqRect);
    SDL_RenderDrawLine(gRenderer, freqRect.x, freqRect.y + INPUT_HEIGHT, freqRect.x + INPUT_WIDTH, freqRect.y + INPUT_HEIGHT);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, userInput.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    // Render text inside the input field
    for (size_t i = 0; i < userFreqInput.size(); ++i)
    {
        char c = userFreqInput[i];
        std::string charString(1, c);

        // Render each character individually
        SDL_Surface *charSurface = SDL_CreateRGBSurfaceWithFormat(0, 10, 20, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_FillRect(charSurface, NULL, 0); // Fill with transparent color

        // Render text on the character surface
        textSurface = TTF_RenderText_Solid(font, charString.c_str(), textColor);
        SDL_Rect textRect = {0, 0, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, charSurface, &textRect);

        SDL_Texture *charTexture = SDL_CreateTextureFromSurface(gRenderer, charSurface);

        SDL_Rect charRect = {freqRect.x + 10 + i * 10, freqRect.y + 5, 10, 20};
        SDL_RenderCopy(gRenderer, charTexture, NULL, &charRect);

        SDL_FreeSurface(charSurface);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(charTexture);
    }
}

// input box for frequency.

void renderForm_amplitude()
{
    // Render input field
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &ampRect);
    SDL_RenderDrawLine(gRenderer, ampRect.x, ampRect.y + INPUT_HEIGHT, ampRect.x + INPUT_WIDTH, ampRect.y + INPUT_HEIGHT);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, userInput.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    // Render text inside the input field
    for (size_t i = 0; i < userAmpInput.size(); ++i)
    {
        char c = userAmpInput[i];
        std::string charString(1, c);

        // Render each character individually
        SDL_Surface *charSurface = SDL_CreateRGBSurfaceWithFormat(0, 10, 20, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_FillRect(charSurface, NULL, 0); // Fill with transparent color

        // Render text on the character surface
        textSurface = TTF_RenderText_Solid(font, charString.c_str(), textColor);
        SDL_Rect textRect = {0, 0, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, charSurface, &textRect);

        SDL_Texture *charTexture = SDL_CreateTextureFromSurface(gRenderer, charSurface);

        SDL_Rect charRect = {ampRect.x + 10 + i * 10, ampRect.y + 5, 10, 20};
        SDL_RenderCopy(gRenderer, charTexture, NULL, &charRect);

        SDL_FreeSurface(charSurface);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(charTexture);
    }
}

// input box for amplitude.

void renderForm()
{
    // Render input field
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &inputRect);
    SDL_RenderDrawLine(gRenderer, inputRect.x, inputRect.y + INPUT_HEIGHT, inputRect.x + INPUT_WIDTH, inputRect.y + INPUT_HEIGHT);

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, userInput.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    // Render text inside the input field
    for (size_t i = 0; i < userInput.size(); ++i)
    {
        char c = userInput[i];
        std::string charString(1, c);

        // Render each character individually
        SDL_Surface *charSurface = SDL_CreateRGBSurfaceWithFormat(0, 10, 20, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_FillRect(charSurface, NULL, 0); // Fill with transparent color

        // Render text on the character surface
        textSurface = TTF_RenderText_Solid(font, charString.c_str(), textColor);
        SDL_Rect textRect = {0, 0, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, charSurface, &textRect);

        SDL_Texture *charTexture = SDL_CreateTextureFromSurface(gRenderer, charSurface);

        SDL_Rect charRect = {inputRect.x + 10 + i * 10, inputRect.y + 5, 10, 20};
        SDL_RenderCopy(gRenderer, charTexture, NULL, &charRect);

        SDL_FreeSurface(charSurface);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(charTexture);
    }

    // Render button
    SDL_SetRenderDrawColor(gRenderer, 0xC0, 0xC0, 0xC0, 0xFF);
    SDL_RenderFillRect(gRenderer, &buttonRect);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &buttonRect);

    // Render text inside the button
    const char *buttonText = "CLEAR";

    // Render each character individually
    for (size_t i = 0; i < strlen(buttonText); ++i)
    {
        char c = buttonText[i];
        std::string charString(1, c);

        SDL_Surface *charSurface = SDL_CreateRGBSurfaceWithFormat(0, 10, 20, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_FillRect(charSurface, NULL, 0); // Fill with transparent color

        // Render text on the character surface
        textSurface = TTF_RenderText_Solid(font, charString.c_str(), textColor);
        SDL_Rect textRect = {0, 0, textSurface->w, textSurface->h};
        SDL_BlitSurface(textSurface, NULL, charSurface, &textRect);

        SDL_Texture *charTexture = SDL_CreateTextureFromSurface(gRenderer, charSurface);

        SDL_Rect charRect = {buttonRect.x + 10 + i * 10, buttonRect.y + 5, 10, 20};
        SDL_RenderCopy(gRenderer, charTexture, NULL, &charRect);

        SDL_FreeSurface(charSurface);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(charTexture);
    }
}

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

    return true;
}

void closeSDL()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void draw_grid_digital()
{
    // Set draw color for the grid lines
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);


    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);

    // Draw vertical lines
    for (int i = 0; i <= 800; i += scale)
    {
        SDL_RenderDrawLine(gRenderer, i, 60, i, 600);
    }
}

void draw_grid_analog()
{
    // Set draw color for the grid lines
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);
    // Draw horizontal lines
    for (int y = 60; y < SCREEN_HEIGHT_A; y += 20)
    {
        SDL_RenderDrawLine(gRenderer, 0, y, SCREEN_WIDTH_A, y);
    }

    // Draw vertical lines
    for (int x = 0; x < SCREEN_WIDTH_A; x += 20)
    {
        SDL_RenderDrawLine(gRenderer, x, 60, x, SCREEN_HEIGHT_A);
    }

    // color of x axis
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);

    
}

void draw_continuous_wave(SDL_Renderer *renderer, double (*wave_function)(double, double, double), double frequency, double amplitude, Uint8 color[4])
{
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);

    const int points = SCREEN_WIDTH_A; // Number of points to draw

    for (int i = 0; i < points - 1; ++i)
    {
        double time1 = i / 100.0; // Adjust the time scale as needed
        double time2 = (i + 1) / 100.0;

        double y1 = wave_function(frequency, amplitude, time1) + SCREEN_HEIGHT_A / 2; // Adjust frequency and amplitude as needed
        double y2 = wave_function(frequency, amplitude, time2) + SCREEN_HEIGHT_A / 2;

        SDL_RenderDrawLine(renderer, i, static_cast<int>(y1), i + 1, static_cast<int>(y2));
    }
}
