#include <iostream>
#include <string>

int main() {
    std::string line;
    bool chars[256] = { false };
    bool ok;
    int to_check = 14;

    std::getline(std::cin, line);
    for (int i = to_check - 1; i < line.size(); i++) {
        ok = true;
        for (int j = 0; j < to_check; j++) {
            if (chars[line.at(i - j)]) {
                ok = false;
            }
            chars[line.at(i - j)] = true;
        }

        if (ok) {
            std::cout << (i + 1) << std::endl;
            return 0;
        }

        for (int j = 0; j < to_check; j++) {
            chars[line.at(i - j)] = false;
        }
    }
    return 0;
}
