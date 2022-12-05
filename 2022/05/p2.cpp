#include <iostream>
#include <string>

class StackItem {
public:
    StackItem(char value) : next(NULL), value(value) {}

    StackItem *next;
    char value;
};

int main() {
    int phase = 0;
    int sum = 0;
    int stacks_count;
    StackItem **stacks;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (phase == 0) {
            stacks_count = (line.size() + 1) / 4;
            stacks = new StackItem*[stacks_count];
            phase++;
        }

        if (phase == 1) {
            if (line.at(1) == '1') {
                phase = 2;
            } else {
                for (int i = 0; i < stacks_count; i++) {
                    char ch = line.at(i * 4 + 1);
                    if (ch != ' ') {
                        StackItem *current = new StackItem(ch);
                        StackItem **existing = &stacks[i];

                        while (*existing != NULL) {
                            existing = &(*existing)->next;
                        }
                        *existing = current;
                    }
                }
            }
        } else if (phase == 2) {
            if (line.size() == 0) {
                phase = 3;
            }
        } else {
            int from = line.find("from");
            int to = line.find("to");

            int count = stoi(line.substr(5, from - 6));
            int from_s = stoi(line.substr(from + 5, to - from - 6)) - 1;
            int to_s = stoi(line.substr(to + 3, line.size() - to - 3)) - 1;

            std::cout << from_s << " " << to_s << std::endl;
            StackItem *existing = stacks[from_s];
            StackItem *first = existing;

            for (count--; count > 0; count--) {
                StackItem *next = existing->next;

                existing = next;
            }
            stacks[from_s] = existing->next;
            existing->next = stacks[to_s];
            stacks[to_s] = first;

            for (int i = 0; i < stacks_count; i++) {
                StackItem *existing = stacks[i];
                while (existing != NULL) {
                    StackItem *last = existing;

                    std::cout << existing->value;

                    existing = existing->next;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
    for (int i = 0; i < stacks_count; i++) {
        std::cout << stacks[i]->value;
    }
    std::cout << std::endl;
    for (int i = 0; i < stacks_count; i++) {
        StackItem *existing = stacks[i];
        while (existing != NULL) {
            StackItem *last = existing;

            existing = existing->next;
            delete last;
        }
    }
    delete[] stacks;
    return 0;
}
