#include <iostream>
#include <string>
#include <array>

int main() {
    int sum = 0;
    std::string line;
    std::array<std::string, 9> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    while (std::getline(std::cin, line)) {
        int first = -1;
        int last = -1;


        for (int i = 0; i < line.size(); i++) {
            int c = line.at(i);
            int v = -1;

            if (c >= '0' && c <= '9') {
                v = c - '0';
            } else {
                for (int j = 0; j < nums.size(); j++) {
                    if (line.rfind(nums[j], i) == i) {
                        v = j + 1;
                        break;
                    }
                }

            }

            if (v != -1) {
                if (first == -1) {
                    first = v;
                }
                last = v;
            }

        }

        sum += 10 * first + last;
    }
    std::cout << sum;
    return 0;
}
