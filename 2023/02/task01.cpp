#include <iostream>
#include <string>

int main() {
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        int state = 0;
        int id = 0;
        int value = 0;

        for (int i = 5; i < line.size(); i++) {
            int c = line.at(i);

            switch (state) {
            case 0:
                if (c >= '0' && c <= '9') {
                    id = 10 * id + (c - '0');
                } else {
                    // std::cout << "id: " << id << std::endl;
                    state = 1;
                    i++;
                }
                break;
            case 1:
                if (c >= '0' && c <= '9') {
                    value = 10 * value + (c - '0');
                } else {
                    // std::cout << "value: " << value << std::endl;
                    state = 2;
                }
                break;
            case 2:
                switch (c) {
                case 'r':
                    if (value > 12) {
                        goto next;
                    }
                    i += 2;
                    break;
                case 'g':
                    if (value > 13) {
                        goto next;
                    }
                    i += 4;
                    break;
                case 'b':
                    if (value > 14) {
                        goto next;
                    }
                    i += 3;
                    break;
                }
                i += 2;
                state = 1;
                value = 0;
                break;
            }
        }
        sum += id;
next:
        1;
    }
    std::cout << sum;
    return 0;
}
