#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

const int width = 7;
const int expected = 2022;
const int start_x = 2;
const int start_y = 3;
const int rocks_count = 5;
const int rocks_size_x = 4;
const int rocks_size_y = 4;
const int rocks[rocks_count][rocks_size_y][rocks_size_x] = {
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
};
const int rocks_height[rocks_count] = {1, 3, 3, 4, 2};
const int rocks_width[rocks_count] = {4, 3, 3, 1, 2};

int state[4 * expected + 10][width] = {0};
int current_push = 0;
int current_action = 0;
int current_rock = 0;
int top_pos = 0;
int count = 0;
int curr_x = 0;
int curr_y = 0;

bool can_render(int x, int y) {
    for (int ry = 0; ry < rocks_size_y; ry++) {
        for (int rx = 0; rx < rocks_size_x; rx++) {
            if (rocks[current_rock][ry][rx] == 1 && state[y + ry][x + rx] == 1) {
                return false;
            }
        }
    }
    return true;
}

void write(int x, int y) {
    for (int ry = 0; ry < rocks_size_y; ry++) {
        for (int rx = 0; rx < rocks_size_x; rx++) {
            if (rocks[current_rock][ry][rx] == 1) {
                state[y + ry][x + rx] = 1;
            }
        }
    }
}

int main() {
    std::string pushes;

    std::getline(std::cin, pushes);

    while (count < expected) {
        if (current_action == 0) {
            // spawn
            curr_x = 2;
            curr_y = top_pos + 3;
            current_action = 1;
        } else if (current_action == 1) {
            // push
            int push = pushes.at(current_push++);
            if (current_push == pushes.size()) {
                current_push = 0;
            }
            int next_x;
            if (push == '<') {
                next_x = curr_x - 1;
            } else {
                next_x = curr_x + 1;
            }
            if (next_x >= 0 && next_x <= width - rocks_width[current_rock]) {
                if (can_render(next_x, curr_y)) {
                    curr_x = next_x;
                    // std::cout << push << " ok" << std::endl;
                } else {
                    // std::cout << push << " e1" << std::endl;
                }
            } else {
                // std::cout << push << " e2" << std::endl;
            }
            current_action = 2;
        } else {
            // fall
            int next_y = curr_y - 1;
            if (next_y >= 0 && can_render(curr_x, next_y)) {
                curr_y = next_y;
                current_action = 1;
            } else {
                write(curr_x, curr_y);
                if (rocks_height[current_rock] + curr_y > top_pos) {
                    top_pos = rocks_height[current_rock] + curr_y;
                }
                current_rock ++;
                if (current_rock == rocks_count) {
                    current_rock = 0;
                }
                count ++;
                current_action = 0;

                /*
                for (int ry = top_pos; ry >= 0; ry--) {
                    for (int rx = 0; rx < width; rx++) {
                        if (state[ry][rx] == 1) {
                            std::cout << "#";
                        } else {
                            std::cout << ".";
                        }
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl; */
            }
        }
    }
    std::cout << top_pos << std::endl;

    return 0;
}
