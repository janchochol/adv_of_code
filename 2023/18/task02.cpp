#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>

struct instr {
    instr(bool lr_, long len_) {
        lr = lr_;
        len = len_;
    }
    bool lr;
    long len;
};

int unhex(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return c - 'a' + 10;
}

int main() {
    std::string line;
    std::vector<instr> instrs;

    long sum = 0;

    while (std::getline(std::cin, line)) {
        int v = 0;
        int i;
        bool lr;

        for (i = 2; line.at(i) != ' '; i++) {
        }
        for (int j = 0; j < 5; j++) {
            v = 16 * v + unhex(line.at(i + j + 3));
        }
        sum += v;
        switch(line.at(i + 5 + 3)) {
            case '0':
                lr = true;
                break;
            case '1':
                lr = false;
                break;
            case '2':
                lr = true;
                v = -v;
                break;
            case '3':
                lr = false;
                v = -v;
                break;
        }
        // std::cout << lr << " " << v << std::endl;
        instrs.emplace_back(lr, v);
    }

    long x = 0;
    long y = 0;

    int s = instrs.size();
    for (int i = 0; i < s; i++) {
        long xx = x;
        long yy = y;
        if (instrs[(i + 1) % s].lr) {
            xx += instrs[(i + 1) % s].len;
        } else {
            yy += instrs[(i + 1) % s].len;
        }
        sum += x * yy - xx * y;
        x = xx;
        y = yy;
    }

    sum = sum / 2 + 1;
   
    std::cout << sum << std::endl;

    return 0;
}
