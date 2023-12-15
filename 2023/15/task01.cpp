#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

int hash(const std::string& str) {
    int h = 0;
    for (int i = 0; i < str.size(); i++) {
        h = ((h + str.at(i)) * 17) % 256;
    }
    return h;
}

int main() {
    std::string line;
    
    std::getline(std::cin, line);

    int last = 0;
    long sum = 0;
    for (int  i = 0; i < line.size(); i++) {
        if (line.at(i) == ',') {
            sum += hash(line.substr(last, i - last));
            last = i + 1;
        }
    }
    sum += hash(line.substr(last, line.size() - last));

    std::cout << sum << std::endl;
    return 0;
}
