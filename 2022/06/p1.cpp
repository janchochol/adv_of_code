#include <iostream>
#include <string>

int main() {
    std::string line;
    bool chars[256] = { false };
    bool ok;

    std::getline(std::cin, line);
    for (int i = 3; i < line.size(); i++) {
        ok = true;
        chars[line.at(i)] = true;
        if (chars[line.at(i - 1)]) {
            ok = false;
        }
        chars[line.at(i - 1)] = true;
        if (chars[line.at(i - 2)]) {
            ok = false;
        }
        chars[line.at(i - 2)] = true;
        if (chars[line.at(i - 3)]) {
            ok = false;
        }

        if (ok) {
            std::cout << (i + 1) << std::endl;
            return 0;
        }

        chars[line.at(i)] = false;
        chars[line.at(i - 1)] = false;
        chars[line.at(i - 2)] = false;
    }
    return 0;
}
