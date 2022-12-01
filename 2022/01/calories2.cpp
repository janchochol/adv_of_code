#include <iostream>
#include <string>

int main() {
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.size() == 0) {
            if (sum >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = sum;
            } else if (sum >= max2) {
                max3 = max2;
                max2 = sum;
            } else if (sum >= max3) {
                max3 = sum;
            }
            sum = 0;
        } else {
                sum += stoi(line);
        }
    }
    if (sum >= max1) {
        max3 = max2;
        max2 = max1;
        max1 = sum;
    } else if (sum >= max2) {
        max3 = max2;
        max2 = sum;
    } else if (sum >= max3) {
        max3 = sum;
    }
    std::cout << max1 + max2 + max3;
    return 0;
}
