#include <iostream>
#include <string>
#include <string.h>
#include <vector>

int main() {
    std::string line;
    int off, counta, countb;
    bool win[100];
    int sum = 0;

    while (std::getline(std::cin, line)) {
        int cur = 0;
        if (line.size() == 48) {
            off = 8;
            counta = 5;
            countb = 8;
        } else {
            off = 10;
            counta = 10;
            countb = 25;
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
                if (cur == 0) {
                    cur = 1;
                } else {
                    cur = 2 * cur;
                }
            }
        }
        sum += cur;

    }

    std::cout << sum << std::endl;
    return 0;
}
