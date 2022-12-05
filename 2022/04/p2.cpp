#include <iostream>
#include <string>

int main() {
    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        int group_delim = line.find(",");
        int split1 = line.find("-");
        int split2 = line.find("-", group_delim + 1);

        int from1 = stoi(line.substr(0, split1));
        int to1 = stoi(line.substr(split1 + 1, group_delim - split1 - 1));
        int from2 = stoi(line.substr(group_delim + 1, split2 - group_delim - 1));
        int to2 = stoi(line.substr(split2 + 1, line.size() - split2));

        if (
            (from1 <= from2 && to2 <= to1) ||
            (from2 <= from1 && to1 <= to2) ||
            (from1 <= from2 && from2 <= to1) ||
            (from2 <= from1 && from1 <= to2)
           ) {
            sum++;
        }
    }
    std::cout << sum;
    return 0;
}
