#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <array>

int main() {
    std::string line;
    std::string inst;
    std::map<std::string, std::pair<std::string, std::string>> map;
    int state = 0;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (state == 0) {
            inst = std::move(line);
            state++;
        } else {
            map[line.substr(0, 3)] = std::make_pair(line.substr(7, 3), line.substr(12, 3));
        }
    }
    std::string node = "AAA";
    int pos = 0;
    while(true) {
        char c = inst.at(pos++ % inst.length());

        if (c == 'L') {
            node = map[node].first;
        } else {
            node = map[node].second;
        }
        if (node == "ZZZ") {
            std::cout << pos << std::endl;
            break;
        }
    }
    return 0;
}
