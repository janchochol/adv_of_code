#include <iostream>
#include <string>

int main() {
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        bool present1[256] = {false};
        bool present2[256] = {false};

        for (int i = 0; i < line.size(); i++) {
            present1[line.at(i)] = true;
        }

        std::getline(std::cin, line);
        for (int i = 0; i < line.size(); i++) {
            present2[line.at(i)] = true;
        }

        std::getline(std::cin, line);
        for (int i = 0; i < line.size(); i++) {
            char ch = line.at(i);
            if(present1[ch] && present2[ch]) {
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
