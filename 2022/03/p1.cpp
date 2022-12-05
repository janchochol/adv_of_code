#include <iostream>
#include <string>

int main() {
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        bool present[256] = {false};

        int i = 0;
        for (; i < line.size() / 2; i++) {
            present[line.at(i)] = true;
        }
        for (; i < line.size(); i++) {
            if(present[line.at(i)]) {
                char ch = line.at(i);

                if (ch >= 'a' && ch <= 'z') {
                    sum += ch - 'a' + 1;
                } else {
                    sum += ch - 'A' + 27;
                }
                break;
            }
        }
    }

    std::cout << sum;
    return 0;
}
