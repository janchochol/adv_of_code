#include <iostream>

#define ROCK        0 // 1 win
#define PAPER       1 // 2 win
#define SCISSORS    2 // 0 win

int main() {
    int score = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        char opponent = line.at(0) - 'A';
        char me = line.at(2);

        if (me == 'X') {
            // loose
            score += ((opponent + 2) % 3) + 1;
        } else if (me == 'Y') {
            // draw
            score += 3 + opponent + 1;
        } else {
            // win
            score += 6;
            score += ((opponent + 1) % 3) + 1;
        }
    }
    std::cout << score;
    return 0;
}
