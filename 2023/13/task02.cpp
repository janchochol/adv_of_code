#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>


bool full_match_c(std::vector<std::string>& rows, int c) {
    int smudge = 0;
    for (int i = 0; i < rows[0].size() / 2; i++) {
        if ((c - i) >= 0 && (c + 1 + i) < rows[0].size()) {
            for (int r = 0; r < rows.size(); r++) {
                if (rows[r].at(c - i) != rows[r].at(c + 1 + i)) {
                    smudge++;
                }
                if (smudge > 1) {
                    return false;
                }
            }
        }
    }
    return (smudge == 1);
}

bool full_match_r(std::vector<std::string>& rows, int r) {
    int smudge = 0;
    for (int i = 0; i < rows.size() / 2; i++) {
        if ((r - i) >= 0 && (r + 1 + i) < rows.size()) {
            for (int c = 0; c < rows[0].size(); c++) {
                if (rows[r - i].at(c) != rows[r + 1 + i].at(c)) {
                    smudge++;
                }
                if (smudge > 1) {
                    return false;
                }
            }
        }
    }
    return (smudge == 1);
}


long check(std::vector<std::string>& rows) {
    for (int c = 0; c < rows[0].size() - 1; c++) {
        if (full_match_c(rows, c)) {
            return (c + 1);
        }
    }
    for (int r = 0; r < rows.size() - 1; r++) {
        if (full_match_r(rows, r)) {
            return 100 * (r + 1);
        }
    }
    return 0;
}


int main() {
    std::string line;
    std::vector<std::string> rows;
    long sum = 0;

    while (std::getline(std::cin, line)) {
        if (line.size() == 0) {
            sum += check(rows);
            rows.clear();
        } else {
            rows.emplace_back(std::move(line));
        }
    }

    sum += check(rows);
    std::cout << sum << std::endl;
    return 0;
}
