#include <iostream>
#include <string>

int main() {
    std::string line;
    int x = 1;
    int cycle = 1;
    int instr_cycles;
    int instr_change;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        if (line.at(0) == 'a') {
            instr_change = stoi(line.substr(5));
            instr_cycles = 2;
        } else {
            instr_change = 0;
            instr_cycles = 1;
        }

        // std::cout << line << std::endl;
        for (int i = 0; i < instr_cycles; i++) {
            if (i == instr_cycles - 1) {
                x += instr_change;
            }
            cycle++;
            // std::cout << cycle << ":" << x << std::endl;
            if ((cycle % 40) == 20 ) {
                // std::cout << cycle << "*" << x << "=" << (cycle * x) << std::endl;
                sum += cycle * x;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
