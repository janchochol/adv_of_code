#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main() {
    std::string line;
    int off, counta, countb;
    bool win[100];
    int cards = 0;
    int pos = 0;
    int *counts = nullptr;

    while (std::getline(std::cin, line)) {
        int cur = 0;
        if(counts == nullptr) {
            if (line.size() == 48) {
                off = 8;
                counta = 5;
                countb = 8;
                cards = 6;
            } else {
                off = 10;
                counta = 10;
                countb = 25;
                cards = 204;
            }
            counts = new int[cards];
            for (int i = 0; i < cards; i++) {
                counts[i] = 1;
            }
        }
        memset(win, 0, sizeof(win));

        for (int i = 0; i < counta; i++) {
            int a = line.at(off + 3 * i);
            if (a == ' ') {
                a = '0';
            }
            win[10 * (a - '0') + line.at(off + 3 * i + 1) - '0'] = true;
        }
        for (int i = 0; i < countb; i++) {
            int a = line.at(off + 3 * counta + 2 + 3 * i);
            if (a == ' ') {
                a = '0';
            }
            if(win[10 * (a - '0') + line.at(off + 3 * counta + 2 + 3 * i + 1) - '0']) {
                cur ++;
            }
        }
        // std::cout << pos << ":" << cur << std::endl;
        for (int i = 0; i < cur; i++) {
            if (pos + i + 1 < cards) {
                counts[pos + i + 1] += counts[pos];
            }
        }
        pos++;
    }
    int sum = 0;
    for (int i = 0; i < cards; i++) {
        sum += counts[i];
    }
    delete [] counts;

    std::cout << sum << std::endl;
    return 0;
}
