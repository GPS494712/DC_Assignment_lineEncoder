

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const int INPUT_WIDTH = 680;
int INPUT_HEIGHT = 30;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 40;

const int MENU_WIDTH = 200;
const int MENU_HEIGHT = 40;
const int MAIN_BOX_WIDTH = 200;
const int MAIN_BOX_HEIGHT = 30;

const char *selectedMenuItem = "";

const char *menuItems[] = {"NRZ-L", "NRZ-I", "Manchester", "D-Manchester", "AMI", "HDB3", "B8ZS"};
const int numMenuItems = sizeof(menuItems) / sizeof(menuItems[0]);
const char *menuItemsAnalog[] = {"Sine", "Cosine", "Triangle"};
const int numMenuItemsAnalog = sizeof(menuItemsAnalog) / sizeof(menuItemsAnalog[0]);

const char *buttonText = "CLEAR";

const int SCREEN_WIDTH_A = 800;
const int SCREEN_HEIGHT_A = 600;
const double PI = 3.141592653589793238462643383279502884;
const float SAMPLE_RATE = 0.125;

const int points = SCREEN_WIDTH_A; // Number of points to draw

float scale = 160;
bool isMenuVisible = false;