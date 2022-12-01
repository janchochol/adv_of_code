#include <iostream>
#include <string>

int main() {
    int max = 0;
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.size() == 0) {
            if (sum > max) {
                max = sum;
            }
            sum = 0;
        } else {
            sum += stoi(line);
        }
    }
    if (sum > max) {
        max = sum;
    }
    std::cout << max;
    return 0;
}
