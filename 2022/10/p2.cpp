#include <iostream>
#include <string>

int main() {
    std::string line;
    int x = 1;
    int cycle = 1;
    int instr_cycles;
    int instr_change;
    int crt = 0;

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
            if ((crt >= x - 1) && (crt <= x + 1)) {
                std::cout << "#";
            } else {
                std::cout << ".";
            }
            crt++;
            if (crt == 40) {
                crt = 0;
                std::cout << std::endl;
            }

            if (i == instr_cycles - 1) {
                x += instr_change;
            }
            cycle++;
            // std::cout << cycle << ":" << x << std::endl;
        }
    }

    return 0;
}
