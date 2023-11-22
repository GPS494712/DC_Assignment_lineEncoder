#include <iostream>
#include <vector>
#include <unordered_map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "functions.c++"
#include "input_reform.c++"
#include "visuals.c++"

enum SignalType
{
    ANALOG,
    DIGITAL
};

bool amplitudeInputActive = false;

SignalType selectedSignal = ANALOG;

void render_radio_button(SDL_Renderer *renderer, const char *text, int x, int y, bool selected)
{
    SDL_Rect outerRect = {x, y, 20, 20};
    SDL_Rect innerRect = {x + 5, y + 5, 10, 10};

    // Draw radio button outer circle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &outerRect);

    // Draw radio button inner circle if selected
    if (selected)
    {
        SDL_RenderFillRect(renderer, &innerRect);
    }

    // Render radio button label
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect destRect = {x + 30, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// In the main loop, call this function to render the radio buttons
void render_radio_buttons(SDL_Renderer *renderer)
{
    // Assuming TTF font is initialized and available globally

    // Render Analog radio button
    render_radio_button(renderer, "Analog", 10, 10, selectedSignal == ANALOG);

    // Render Digital radio button
    render_radio_button(renderer, "Digital", 10, 40, selectedSignal == DIGITAL);
}

// In the main loop, handle mouse click events to update the selected signal
void handle_mouse_click(SDL_Event &event)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    std::cout << selectedSignal << std::endl;
}

int main(int argc, char *args[])
{
    std ::unordered_map<int, std ::string> map;
    map[-40] = "00";
    map[-20] = "01";
    map[20] = "11";
    map[40] = "10";

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
    int def_a = 0;
    int def_d = 0;
    // std::string input_a2d = SamplingWave(map);
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
                if (selectedSignal == ANALOG)
                {
                    std::string &activeField = amplitudeInputActive ? userAmpInput : userFreqInput;
                    if (activeField.length() < 4 && event.text.text[0] >= '0' && event.text.text[0] <= '9')
                    {
                        activeField += event.text.text;
                    }
                }
                else
                {
                    userInput += event.text.text;
                    std::cout << "Longest pallindrome : " << longestPalindrome(userInput) << std::endl;
                    // std::cout << "Longest pallindrome is : " << pallindrome(userInput) << endl;
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                // Handle backspace for the input field
                if (event.key.keysym.sym == SDLK_BACKSPACE && userInput.length() > 0)
                {
                    userInput.pop_back();
                }
                else if(event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS || event.key.keysym.sym == SDLK_p){
                    if (selectedSignal == ANALOG)
                    {

                        std::string &activeField = amplitudeInputActive ? userAmpInput : userFreqInput;
                        int test = stoi(activeField);
                        test++;
                        activeField = std::to_string(test);
                    }
                }
                else if(event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS){
                    if (selectedSignal == ANALOG)
                    {

                        std::string &activeField = amplitudeInputActive ? userAmpInput : userFreqInput;
                        int test = stoi(activeField);
                        test--;
                        activeField = std::to_string(test);
                    }
                }
                
                // else if (selectedSignal == ANALOG)
                // {

                //     std::string &activeField = amplitudeInputActive ? userAmpInput : userFreqInput;
                //     if(event.key.keysym.sym == SDLK_PLUS){
                //         int test = stoi(activeField);
                //         test++;
                //         activeField = std::to_string(test);
                //     }
                //     else if(event.key.keysym.sym == SDLK_MINUS){
                //         int test = stoi(activeField);
                //         test--;
                //         activeField = std::to_string(test);
                //     }
                    
                // }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= 800 && mouseX <= 840 && mouseY >= 500 && mouseY <= 540)
                {
                    // Handle text input for the input field
                    amplitudeInputActive = false;
                }
                else if (mouseX >= 850 && mouseX <= 890 && mouseY >= 500 && mouseY <= 540)
                {

                    // Handle text input for the input field
                    amplitudeInputActive = true;
                }

                if (mouseX >= 10 && mouseX <= 30 && mouseY >= 10 && mouseY <= 30)
                {
                    selectedSignal = ANALOG;
                }
                else if (mouseX >= 10 && mouseX <= 30 && mouseY >= 40 && mouseY <= 60)
                {
                    selectedSignal = DIGITAL;
                }
                // Check if the mouse click is inside the button
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + BUTTON_WIDTH &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + BUTTON_HEIGHT)
                {
                    // Handle button click (you can add your logic here)
                    std::cout << "Button clicked! User Input: " << userInput << std::endl;
                    userInput = ""; // Clear the input field after clicking the button
                    // std::cout << SamplingWave(map, userFreqInput, userAmpInput) << std::endl;
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
                    for (int i = 0; i < (selectedSignal ? numMenuItems : numMenuItemsAnalog); i++)
                    {
                        if (mouseX >= 800 && mouseX <= 800 + MENU_WIDTH &&
                            mouseY >= 40 + i * MENU_HEIGHT && mouseY <= 40 + i * MENU_HEIGHT + MENU_HEIGHT)
                        {
                            std::cout << "Menu item clicked: " << menuItems[i] << std::endl;
                            if (selectedSignal == 1)
                            {
                                def_d = i;
                            }
                            else
                            {
                                def_a = i;
                            }
                            selectedMenuItem = selectedSignal ? menuItems[i] : menuItemsAnalog[i];
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

        selectedMenuItem = selectedSignal ? menuItems[def_d] : menuItemsAnalog[def_a];

        render_radio_buttons(gRenderer);
        if (selectedSignal == ANALOG)
        {

            draw_grid_analog();
            renderMenu_analog();
            renderComboBox_analog();
            renderForm_amplitude();
            renderForm_frequency();
            int frequency_ = stoi(userFreqInput);
            int amplitude_ = stoi(userAmpInput);
            Uint8 red[4] = {0, 0, 255, 255};
            Uint8 green[4] = {1, 100, 32, 255};
            Uint8 blue[4] = {255, 0, 0, 255};

            switch (def_a)
            {
            case 0:
                draw_continuous_wave(gRenderer, sine_wave, frequency_, amplitude_, red);
                break;
            case 1:
                draw_continuous_wave(gRenderer, cosine_wave, frequency_, amplitude_, green);
                break;
            case 2:
                draw_continuous_wave(gRenderer, triangle_wave, frequency_, amplitude_, blue);
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                break;
            }
        }
        else
        {
            draw_grid_digital();
            renderMenu_digital();
            renderComboBox_digital();
            renderForm();
            switch (def_d)
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
        }


        if (n >= float(800 / scale))
        {
            scale = scale / 2;
        }
        if (n == float(800 / (scale * 2)))
        {
            scale = scale * 2;
        }


        SDL_RenderPresent(gRenderer);
    }

    closeSDL();

    return 0;
}