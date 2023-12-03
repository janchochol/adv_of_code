#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(std::cin, line)) {
        lines.emplace_back(std::move(line));
    }

    int width = lines[0].length();
    int height = lines.size();

    int *numbers = new int[width * height];
    int *pos = new int[width * height];
    bool *valid = new bool[width * height];

    // std::cout << width << "x" << height << std::endl;

    int idx = 0;
    for(int y = 0; y < height; y++) {
        int number = 0;
        for(int x = 0; x < width; x++) {
            int c = lines[y].at(x);

            pos[x * width + y] = -1;
            if (c >= '0' && c <= '9') {
                // std::cout << x << "x" << y << ":" << idx << std::endl;
                pos[x * width + y] = idx;
                number = 10 * number + c - '0';
            }
            if((c < '0' || c > '9' || (x == width - 1)) && number != 0) {
                // std::cout << idx << ":" << number << std::endl;
                numbers[idx] = number;
                valid[idx] = false;
                idx ++;
                number = 0;
            }
        }
    }

    int sum = 0;
    for(int x = 0; x < width; x++) {
        int number = 0;
        for(int y = 0; y < height; y++) {
            int c = lines[y].at(x);

            if (c == '*') {
                int matches = 0;
                int mult = 1;

                for (int xx = x - 1; xx <= x + 1; xx++) {
                    for (int yy = y - 1; yy <= y + 1; yy++) {
                        if (xx >= 0 && xx <= width - 1 && yy >= 0 && yy <= height - 1) {
                            int p = pos[xx * width + yy];
                            if (p != -1) {
                                if (valid[p] == false) {
                                    // std::cout << xx << "x" << yy << " " << p << std::endl;
                                    mult *= numbers[p];
                                    matches++;
                                }
                                valid[p] = true;
                            }
                        }
                    }
                }
                for (int xx = x - 1; xx <= x + 1; xx++) {
                    for (int yy = y - 1; yy <= y + 1; yy++) {
                        if (xx >= 0 && xx <= width - 1 && yy >= 0 && yy <= height - 1) {
                            int p = pos[xx * width + yy];
                            if (p != -1) {
                                valid[p] = false;
                            }
                        }
                    }
                }
                // std::cout << x << "x" << y << ": " << matches << " - " << mult << std::endl;
                if (matches == 2) {
                    sum += mult;
                }
            }
        }
    }

    delete [] valid;
    delete [] pos;
    delete [] numbers;

    std::cout << sum << std::endl;
    return 0;
}
