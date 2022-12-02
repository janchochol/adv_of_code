#include <iostream>

#define ROCK        0
#define PAPER       1
#define SCISSORS    2

int main() {
    int score = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        char opponent = line.at(0) - 'A';
        char me = line.at(2) - 'X';

        score += me + 1;
        if (opponent == me) {
            score += 3;
        } else if (
                   (me == ROCK && opponent == SCISSORS) ||
                   (me == PAPER && opponent == ROCK) ||
                   (me == SCISSORS && opponent == PAPER)
                  ) {
            score += 6;
        }
    }
    std::cout << score;
    return 0;
}
