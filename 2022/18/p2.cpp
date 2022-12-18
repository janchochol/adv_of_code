#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

struct xyz {
    xyz(int x, int y, int z) : x(x), y(y), z(z) {}

    int x, y, z;
};

int main() {
    std::string line;
    const int max = 30;

    bool pixels[max][max][max] = { false };
    bool tpixels[max][max][max] = { false };

    int max_x = 0, max_y = 0, max_z = 0;

    while(std::getline(std::cin, line)) {
        int comma1 = line.find(',');
        int comma2 = line.find(',', comma1 + 1);

        int x = stoi(line.substr(0, comma1));
        int y = stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
        int z = stoi(line.substr(comma2 + 1, line.size() - comma2 - 1));

        if(x > max_x) {
            max_x = x;
        }
        if(y > max_y) {
            max_y = y;
        }
        if(z > max_z) {
            max_z = z;
        }

        pixels[x][y][z] = true;
    }

    std::cout << max_x << " " << max_y << " " << max_z << " " << std::endl;
    std::queue<xyz> q;

    for (int x = 0; x < max; x++) {
        for (int y = 0; y < max; y++) {
            for (int z = 0; z < max; z++) {
                if (x == 0 || x == max - 1 || y == 0 || y == max - 1 || z == 0 || z == max - 1) {
                    if (pixels[x][y][z] == false) {
                        tpixels[x][y][z] = true;
                        q.push(xyz(x, y, z));
                    }
                }
            }
        }
    }

    while (!q.empty()) {
        struct xyz &c = q.front();

        if (c.x > 0 && pixels[c.x - 1][c.y][c.z] == false && tpixels[c.x - 1][c.y][c.z] == false) {
            tpixels[c.x - 1][c.y][c.z] = true;
            q.push(xyz(c.x - 1, c.y, c.z));
        }
        if (c.x < max - 1 && pixels[c.x + 1][c.y][c.z] == false && tpixels[c.x + 1][c.y][c.z] == false) {
            tpixels[c.x + 1][c.y][c.z] = true;
            q.push(xyz(c.x + 1, c.y, c.z));
        }

        if (c.y > 0 && pixels[c.x][c.y - 1][c.z] == false && tpixels[c.x][c.y - 1][c.z] == false) {
            tpixels[c.x][c.y - 1][c.z] = true;
            q.push(xyz(c.x, c.y - 1, c.z));
        }
        if (c.y < max - 1 && pixels[c.x][c.y + 1][c.z] == false && tpixels[c.x][c.y + 1][c.z] == false) {
            tpixels[c.x][c.y + 1][c.z] = true;
            q.push(xyz(c.x, c.y + 1, c.z));
        }

        if (c.z > 0 && pixels[c.x][c.y][c.z - 1] == false && tpixels[c.x][c.y][c.z - 1] == false) {
            tpixels[c.x][c.y][c.z - 1] = true;
            q.push(xyz(c.x, c.y, c.z - 1));
        }
        if (c.z < max - 1 && pixels[c.x][c.y][c.z + 1] == false && tpixels[c.x][c.y][c.z + 1] == false) {
            tpixels[c.x][c.y][c.z + 1] = true;
            q.push(xyz(c.x, c.y, c.z + 1));
        }

        q.pop();
    }

    int sum = 0;

    for (int x = 0; x < max; x++) {
        for (int y = 0; y < max; y++) {
            for (int z = 0; z < max; z++) {
                if (pixels[x][y][z]) {
                    if (x == 0) {
                        sum ++;
                    } else if (tpixels[x - 1][y][z] && !pixels[x - 1][y][z]) {
                        sum ++;
                    }

                    if (x == max - 1) {
                        sum ++;
                    } else if (tpixels[x + 1][y][z] && !pixels[x + 1][y][z]) {
                        sum ++;
                    }

                    if (y == 0) {
                        sum ++;
                    } else if (tpixels[x][y - 1][z] && !pixels[x][y - 1][z]) {
                        sum ++;
                    }

                    if (y == max - 1) {
                        sum ++;
                    } else if (tpixels[x][y + 1][z] && !pixels[x][y + 1][z]) {
                        sum ++;
                    }

                    if (z == 0) {
                        sum ++;
                    } else if (tpixels[x][y][z - 1] && !pixels[x][y][z - 1]) {
                        sum ++;
                    }

                    if (z == max - 1) {
                        sum ++;
                    } else if (tpixels[x][y][z + 1] && !pixels[x][y][z + 1]) {
                        sum ++;
                    }
                }
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
