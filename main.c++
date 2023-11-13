#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "functions.c++"
#include "input_reform.c++"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int INPUT_WIDTH = 680;
const int INPUT_HEIGHT = 30;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 40;

const int MENU_WIDTH = 200;
const int MENU_HEIGHT = 40;
const int MAIN_BOX_WIDTH = 200;
const int MAIN_BOX_HEIGHT = 30;

const char *selectedMenuItem = "NRZ-L";

float scale = 160;
bool isMenuVisible = false;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;

std::string userInput = "";

TTF_Font *font;
SDL_Color textColor = {0, 0, 255, 255};

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
    for (int i = 0; i <= 800; i += scale)
    {
        SDL_RenderDrawLine(gRenderer, i, 0, i, 600);
    }
}


// Define menu items

// Define menu items
const char *menuItems[] = {"NRZ-L", "NRZ-I", "Manchester", "D-Manchester", "AMI", "HDB3", "B8ZS"};
const int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);

SDL_Rect inputRect = {(100), 0, INPUT_WIDTH, INPUT_HEIGHT};
SDL_Rect buttonRect = {100, 80, BUTTON_WIDTH, BUTTON_HEIGHT};

void renderMenu()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    // SDL_Rect menuRect = {800, 200, MENU_WIDTH, MENU_HEIGHT};
    // SDL_RenderFillRect(gRenderer, &menuRect);

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
void renderComboBox()
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

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Load font
    font = TTF_OpenFont("./Roboto-Regular.ttf", 16); // Replace with the path to your TTF font file
    if (font == NULL)
    {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return 1;
    }
    int def = 0;

    while (!quit)
    {
        int n = userInput.size();
        int arr[n];
        // std::cout << n << std::endl;
        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            // if (e.type == SDL_QUIT)
            // {
            //     quit = true;
            // }
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_TEXTINPUT)
            {
                // Handle text input for the input field
                userInput += event.text.text;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Handle backspace for the input field
                if (event.key.keysym.sym == SDLK_BACKSPACE && userInput.length() > 0)
                {
                    userInput.pop_back();
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if the mouse click is inside the button
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + BUTTON_WIDTH &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + BUTTON_HEIGHT)
                {
                    // Handle button click (you can add your logic here)
                    std::cout << "Button clicked! User Input: " << userInput << std::endl;
                    userInput = ""; // Clear the input field after clicking the button
                }
                else if (mouseX >= inputRect.x && mouseX <= inputRect.x + INPUT_WIDTH &&
                         mouseY >= inputRect.y && mouseY <= inputRect.y + INPUT_HEIGHT)
                {
                    // Handle input field click
                    std::cout << "Input field clicked!" << std::endl;
                }
                else if (mouseX >= 800 && mouseX <= 800 + MENU_WIDTH &&
                         mouseY >= 10 && mouseY <= 10 + MENU_HEIGHT)
                {
                    // Handle menu click
                    std::cout << "Menu clicked!" << std::endl;
                    isMenuVisible = !isMenuVisible;
                }
                else if (isMenuVisible)
                {
                    // Handle menu item click
                    for (int i = 0; i < numMenuItems; i++)
                    {
                        if (mouseX >= 800 && mouseX <= 800 + MENU_WIDTH &&
                            mouseY >= 40 + i * MENU_HEIGHT && mouseY <= 40 + i * MENU_HEIGHT + MENU_HEIGHT)
                        {
                            std::cout << "Menu item clicked: " << menuItems[i] << std::endl;
                            def = i;
                            selectedMenuItem = menuItems[i];
                            isMenuVisible = false;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            arr[i] = userInput[i] - 48;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        // Draw the centered Cartesian plane grid
        drawGrid();

        // Select encoding techniques
        // Nrz_i(arr, n, gRenderer, scale);
        // manchaster(arr, n, gRenderer, scale);
        // d_manchester(arr, n, gRenderer, scale);
        // AMI(arr, n, gRenderer, scale);
        // input_hdb3(arr, n);

        // scramble(arr, n, gRenderer, scale);
        switch (def)
        {
        case 0:
            Nrz_l(arr, n, gRenderer, scale);

            break;
        case 1:
            Nrz_i(arr, n, gRenderer, scale);
            break;
        case 2:
            manchaster(arr, n, gRenderer, scale);
            break;
        case 3:
            d_manchester(arr, n, gRenderer, scale);
            break;
        case 4:
            AMI(arr, n, gRenderer, scale);
            break;
        case 5:
            input_hdb3(arr, n);
            scramble(arr, n, gRenderer, scale);
            break;
        case 6:
            input_b8zs(arr, n);
            scramble(arr, n, gRenderer, scale);
            break;
        default:
            std::cout << "Invalid Input" << std::endl;
            break;
        }

        if (n >= float(800 / scale))
        {
            scale = scale / 2;
        }
        if (n == float(800 / (scale*2)))
        {
            scale = scale * 2 ;
        }

        renderMenu();
        renderComboBox();
        renderForm();

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();

    return 0;
}