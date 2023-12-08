#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <array>
#include <numeric>

int main() {
    std::string line;
    std::string inst;
    std::map<std::string, std::pair<std::string, std::string>> map;
    constexpr int c = 'Z' - 'A' + 1;
    int mapl[c * c * c];
    int mapr[c * c * c];
    std::vector<int> nodes;
    int state = 0;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (state == 0) {
            inst = std::move(line);
            state++;
        } else {
            int a = (int)line.at(0) - 'A' + c * ((int)line.at(1) - 'A' + c * ((int)line.at(2) - 'A'));
            int l = (int)line.at(7) - 'A' + c * ((int)line.at(8) - 'A' + c * ((int)line.at(9) - 'A'));
            int r = (int)line.at(12) - 'A' + c * ((int)line.at(13) - 'A' + c * ((int)line.at(14) - 'A'));
            mapl[a] = l;
            mapr[a] = r;
            if (a / c / c == ('A' - 'A')) {
                // std::cout << a << " " << c << " " << line << std::endl;
                nodes.emplace_back(a);
            }
        }
    }

    inst.append(inst);
    for (int i = 1; i <= inst.length() / 2; i++) {
        int j;
        for (j = i; j <= inst.length() / 2; j++) {
            if (inst.substr(j, i) != inst.substr(0, i)) {
                break;
            }
        }
        if (j >= inst.length() / 2) {
            if (i != inst.length() / 2) {
                std::cerr << "Unsupported input - repeat in path" << std::endl;
            }
            inst = inst.substr(0, i);
            break;
        }
    }
    
    long pos = 0;
    long lcm = 0;
    // long max_done;
    int first[c * c * c];
    for (int i = 0; i< nodes.size(); i++) {
        for (int j = 0; j < c * c * c; j++) {
            first[j] = -1;
        }
        pos = 0;
        first[nodes[i]] = 0;
        long last_z = -1;
        while(true) {
            int done = 0;
            char cc = inst.at(pos++ % inst.length());

            if (cc == 'L') {
                nodes[i] = mapl[nodes[i]];
            } else {
                nodes[i] = mapr[nodes[i]];
            }
            if (nodes[i] / c / c == 'Z' - 'A') {
                if (last_z == -1) {
                    last_z = pos;
                } else {
                    std::cerr << "Unsupported input - more matches in period" << std::endl;
                    return 1;
                }
            }
            if (first[nodes[i]] == -1) {
                first[nodes[i]] = pos;
            } else if((pos - first[nodes[i]]) % inst.length() == 0 ) {
                if (last_z != (pos - first[nodes[i]])) {
                    std::cerr << "Unsupported input - match not aligned with period" << std::endl;
                    return 1;
                }
                break;
            }
        }
        if (i == 0) {
            lcm = last_z;
        } else {
            lcm = std::lcm(lcm, last_z);
        }
    }
    std::cout << lcm << std::endl;
    return 0;
}
