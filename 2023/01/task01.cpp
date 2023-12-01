#include <iostream>
#include <string>

int main() {
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        int first = -1;
        int last = -1;

        for (int i = 0; i < line.size(); i++) {
            int c = line.at(i);

            if (c >= '0' && c <= '9') {
                if (first == -1) {
                    first = c - '0';
                }
                last = c - '0';
            }
        }

        sum += 10 * first + last;
    }
    std::cout << sum;
    return 0;
}
