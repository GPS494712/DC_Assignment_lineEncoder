#include <iostream>
#include <cmath>

double customRoundUp(double number) {
    return std::ceil(number);
}

int main() {
    double value = -0.6;
    double roundedValue = round(value);

    std::cout << "Original value: " << value << std::endl;
    std::cout << "Rounded up value: " << roundedValue << std::endl;

    return 0;
}
