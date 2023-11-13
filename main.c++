#include <iostream>
#include <vector>
#include "SDL2/SDL.h"


#include "functions.c++"
#include"input_reform.c++"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int scale = 40;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

// TTF_Font* font;


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

void drawGrid()
{
    // Set draw color for the grid lines
    SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);

    // Draw horizontal lines
    // for (int i = 0; i <= SCREEN_HEIGHT; i += scale)
    // {
    //     SDL_RenderDrawLine(gRenderer, 0, i, 800, i);
           SDL_RenderDrawLine(gRenderer, 0, 300, 800, 300);
    // }
    // Draw vertical lines
    for (int i = 0; i <= SCREEN_WIDTH; i += scale)
    {
        SDL_RenderDrawLine(gRenderer, i, 0, i, 600);
    }
}

const int INPUT_WIDTH = 200;
const int INPUT_HEIGHT = 30;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 40;

std::string userInput = "";

SDL_Rect inputRect = {(SCREEN_WIDTH - INPUT_WIDTH), 40, INPUT_WIDTH, INPUT_HEIGHT};
SDL_Rect buttonRect = {(SCREEN_WIDTH - INPUT_WIDTH), 80, BUTTON_WIDTH, BUTTON_HEIGHT};

void renderForm() {
    // Render input field
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &inputRect);
    // SDL_RenderDrawLine(gRenderer, inputRect.x, inputRect.y + INPUT_HEIGHT, inputRect.x + INPUT_WIDTH, inputRect.y + INPUT_HEIGHT);

    // SDL_Surface* textSurface = TTF_RenderText_Solid(font, userInput.c_str(), textColor);
    // SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    // SDL_Rect textRect = {inputRect.x + 10, inputRect.y + 5, textSurface->w, textSurface->h};
    // SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);

    // Render button
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(gRenderer, &buttonRect);
    SDL_Surface* textSurface = SDL_CreateRGBSurfaceWithFormat(0, BUTTON_WIDTH, BUTTON_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    // Render text inside the input field
    for (size_t i = 0; i < userInput.size(); ++i) {
        char c = userInput[i];
        std::string charString(1, c);
        // const char* charCStr = charString.c_str();

        
        SDL_Surface* charSurface = SDL_CreateRGBSurfaceWithFormat(0, 10, 20, 32, SDL_PIXELFORMAT_RGBA32);
        if(c == 0){
            SDL_FillRect(charSurface, NULL, SDL_MapRGBA(textSurface->format, 0, 255, 0, 255));
        }
        else{
            SDL_FillRect(charSurface, NULL, SDL_MapRGBA(textSurface->format, 255, 0, 0, 255));
        }

        SDL_Texture* charTexture = SDL_CreateTextureFromSurface(gRenderer, charSurface);

        SDL_Rect charRect = {inputRect.x + 10 + i * 10, inputRect.y + 5, 10, 20};
        SDL_RenderCopy(gRenderer, charTexture, NULL, &charRect);

        SDL_FreeSurface(charSurface);
        SDL_DestroyTexture(charTexture);
    }

    // Render text inside the button
    const char* buttonText = "Submit";
    SDL_FillRect(textSurface, NULL, SDL_MapRGBA(textSurface->format, 192, 192, 192, 255));

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    SDL_Rect textRect = {buttonRect.x + 10, buttonRect.y + 5, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


int main(int argc, char *args[])
{
    // int n;
    // std::cout << "Enter the number of Bits: ";
    // std::cin >> n;
    // std::cout << "Enter the Bits : ";
    // int arr[n];

    // Taking input from user
    // for (int i = 0; i < n; i++)
    // {
    //     std::cin >> arr[i];
    // }

    if (!initSDL())
    {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event event;
    int xOffset = 0;

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            // if (e.type == SDL_QUIT)
            // {
            //     quit = true;
            // }
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_TEXTINPUT) {
                // Handle text input for the input field
                userInput += event.text.text;
            } else if (event.type == SDL_KEYDOWN) {
                // Handle backspace for the input field
                if (event.key.keysym.sym == SDLK_BACKSPACE && userInput.length() > 0) {
                    userInput.pop_back();
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if the mouse click is inside the button
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + BUTTON_WIDTH &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + BUTTON_HEIGHT) {
                    // Handle button click (you can add your logic here)
                    std::cout << "Button clicked! User Input: " << userInput << std::endl;
                    // userInput = "";  // Clear the input field after clicking the button
                }
            }
        }

        int n = userInput.size();
        int arr[n];
        for(int i = 0; i < n; i++){
            arr[i] = userInput[i] - 48;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        // Draw the centered Cartesian plane grid
        drawGrid();

        // Select encoding techniques
        // Nrz_l(arr, n, gRenderer, scale);
        // Nrz_i(arr, n, gRenderer, scale);
        // manchaster(arr, n, gRenderer, scale);
        // d_manchester(arr, n, gRenderer, scale);
        // AMI(arr, n, gRenderer, scale);
        input_hdb3(arr,n);

        scramble(arr, n, gRenderer, scale);
        


        renderForm();

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();

    return 0;
}