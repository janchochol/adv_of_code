#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <functional>


std::size_t hash(std::vector<std::string>& rows) {
    std::size_t h = 0;
    for (const std::string& line: rows) {
        h ^= std::hash<std::string>{}(line) + 0x9e3779b9 + (h << 6) + (h >> 2);
    }
    return h;
}

int main() {
    std::string line;
    std::vector<std::string> rows;
    std::vector<std::string> test;

    while (std::getline(std::cin, line)) {
        rows.emplace_back(std::move(line));
    }

    constexpr int limit = 1000000000;
    constexpr int try_limit = 1000;

    std::size_t hashes[try_limit];
    std::vector<std::string> tests[try_limit];
    bool moved = false;

    for (int c = 1; c < limit; c++) {
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
        for (int y = 0; y < rows.size(); y++) {
            for (int x = 1; x < rows[0].size(); x++) {
                if (rows[y].at(x) == 'O') {
                    for (int mx = x - 1; mx >= 0; mx--) {
                        if (rows[y].at(mx) == '.') {
                            rows[y].at(mx + 1) = '.';
                            rows[y].at(mx) = 'O';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        for (int x = 0; x < rows[0].size(); x++) {
            for (int y = rows.size() - 2; y >= 0; y--) {
                if (rows[y].at(x) == 'O') {
                    for (int my = y + 1; my < rows.size(); my++) {
                        if (rows[my].at(x) == '.') {
                            rows[my - 1].at(x) = '.';
                            rows[my].at(x) = 'O';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        for (int y = 0; y < rows.size(); y++) {
            for (int x = rows[0].size() - 2; x >= 0; x--) {
                if (rows[y].at(x) == 'O') {
                    for (int mx = x + 1; mx < rows[0].size(); mx++) {
                        if (rows[y].at(mx) == '.') {
                            rows[y].at(mx - 1) = '.';
                            rows[y].at(mx) = 'O';
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        if (!moved) {
            if (c >= try_limit) {
                std::cerr << "not enough try_limit!" << std::endl;
                return 1;
            }
            hashes[c] = hash(rows);
            for (const std::string& line: rows) {
                tests[c].emplace_back(line);
            }
            for (int h = 1; h < c; h++) {
                if (hashes[h] == hashes[c]) {
                    bool match = true;
                    for (int y = 0; match && y < rows.size(); y++) {
                        for (int x = 0; x < rows[0].size(); x++) {
                            if (tests[c][y].at(x) != tests[h][y].at(x)) {
                                match = false;
                                break;
                            }
                        }
                    }
                    if (match) {
                        int move = ((limit - h) / (h - c)) * (h - c) + h;
                        // std::cout << h << " " << c << " " << move << std::endl;
                        c = move - 1;
                        moved = true;
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
