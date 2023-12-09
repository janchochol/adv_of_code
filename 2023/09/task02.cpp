#include <iostream>
#include <string>
#include <string.h>
#include <vector>

long process(std::vector<long>& in) {
    std::vector<long> out;
    bool zero = true;

    for (int i = 1; i < in.size(); i++) {
        long v = in[i] - in[i - 1];
        if (v != 0) {
            zero = false;
        }
        out.emplace_back(v);
    }
    if (zero) {
        return 0;
    } else {
        long n = process(out);
        return out[0] - n;
    }
}


int main() {
    std::string line;
    long sum = 0;

    while (std::getline(std::cin, line)) {
        std::vector<long> vals;
        long val = 0;
        bool minus = false;
        for (int i = 0; i < line.size(); i++) {
            char c = line.at(i);
            if (c == '-') {
                minus = !minus;
            } else if (c >= '0' && c <= '9') {
                val = 10 * val + c - '0';
            } else {
                if (minus) {
                    val = -val;
                }
                vals.emplace_back(val);
                val = 0;
                minus = false;
            }
        }
        if (minus) {
            val = -val;
        }
        vals.emplace_back(val);

        long v = vals[0] - process(vals);
        sum += v;
        // std::cout << v << std::endl;
    }
    std::cout << sum << std::endl;
    return 0;
}
