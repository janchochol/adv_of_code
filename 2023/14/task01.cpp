#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>


int main() {
    std::string line;
    std::vector<std::string> rows;

    while (std::getline(std::cin, line)) {
        rows.emplace_back(std::move(line));
    }

    for (int x = 0; x < rows[0].size(); x++) {
        for (int y = 1; y < rows.size(); y++) {
            if (rows[y].at(x) == 'O') {
                for (int my = y - 1; my >= 0; my--) {
                    if (rows[my].at(x) == '.') {
                        rows[my + 1].at(x) = '.';
                        rows[my].at(x) = 'O';
                    } else {
                        break;
                    }
                }
            }
        }
    }
    
    long sum = 0;
   
    for (int y = 0; y < rows.size(); y++) {
        for (int x = 0; x < rows[0].size(); x++) {
            // std::cout << rows[y].at(x);
            if (rows[y].at(x) == 'O') {
                sum += rows.size() - y;
            }
        }
        // std::cout << std::endl;
    }
    
    std::cout << sum << std::endl;
    return 0;
}
