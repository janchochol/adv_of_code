#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

const int width = 7;
const long expected = 1000000000000L;
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

int *state[width];
int current_push = 0;
int current_action = 0;
int current_rock = 0;
int top_pos = 0;
long count = 0;
int curr_x = 0;
int curr_y = 0;

bool can_render(int x, int y) {
    for (int ry = 0; ry < rocks_size_y; ry++) {
        for (int rx = 0; rx < rocks_size_x; rx++) {
            if (rocks[current_rock][ry][rx] == 1 && state[x + rx][y + ry] == 1) {
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
                state[x + rx][y + ry] = 1;
            }
        }
    }
}

struct check {
    int push;
    int rock;
    int x;

    bool operator==(const check &other) const {
        return (push == other.push
                && rock == other.rock
                && x == other.x);
    }

};

struct check_hash {
    std::size_t operator () (const check &p) const {
        auto h1 = std::hash<int>{}(p.push);
        auto h2 = std::hash<int>{}(p.rock);
        auto h3 = std::hash<int>{}(p.x);

        return h1 ^ h2 ^ h3;
    }
};

int main() {
    std::string pushes;
    std::unordered_map<check, std::pair<int, int>, check_hash> known;
    std::unordered_map<check, int, check_hash> found;

    std::getline(std::cin, pushes);

    int period;
    int period_start;
    int phase = 0;
    int previous_top_pos = 0;
    int top_pos_period = 0;
    long top_pos_off = 0;

    for (int i = 0; i < width; i++) {
        state[i] = new int[10000000 + 20];
        std::fill_n(state[i], 10000000 + 20, 0);
    }

    while (count < expected) {
        if (phase == 0 && current_action == 0 ) {
            check pair = {current_push, current_rock, curr_x};

            if (known.find(pair) == known.end()) {
                known[pair] = std::make_pair(count, top_pos);
                found[pair] = 1;
            } else if (found[pair] == 1) {
                known[pair] = std::make_pair(count, top_pos);
                found[pair] = 2;
            } else {
                std::cout << current_push << " " << current_rock << " " << count << " " << known[pair].first << " " << known[pair].second << " " << top_pos << std::endl;
                period_start = known[pair].first;
                top_pos_period = top_pos - known[pair].second;
                period = count - period_start;
                previous_top_pos = top_pos;
                phase = 1;

                known[pair] = std::make_pair(count, top_pos);
            }
        } else if (phase == 1 && top_pos > previous_top_pos) {
            long p1 = period_start;
            long p2 = period;
            long p3 = count - period - period_start;

            if (p3 > 1) {
                phase = 0;
            } else {
                long mul = (expected - p1 - p2 - p3 - 1) / period;

                count += mul * period;
                top_pos_off = mul * top_pos_period;

                std::cout
                    << p1 << " "
                    << p2 << " "
                    << p3 << " "
                    << mul << " "
                    << count << " "
                    << top_pos_off << " "
                    << std::endl;
                phase = 2;
            }
        }
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
                        if (state[rx][ry] == 1) {
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
    std::cout << top_pos << " " << (top_pos_off + top_pos) << std::endl;

    return 0;
}
