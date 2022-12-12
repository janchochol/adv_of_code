#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

int so_far = -1;

class Node {
public:
    Node() {}

    bool is_valid_step(Node &other) {
        return (height >= other.height - 1);
    }

    void bfs_search(std::queue<Node*> &queue, bool *visited, int row_size) {
        Node *pos[] = {l, r, u, d};

        for (int i = 0; i < 4; i++) {
            if (pos[i] && visited[pos[i]->x + pos[i]->y * row_size] == false) {
                visited[pos[i]->x + pos[i]->y * row_size] = true;
                pos[i]->path = path + 1;
                queue.push(pos[i]);
            }
        }
    }

    bool is_end;
    int x, y, height;
    int path;
    Node *l, *r, *u, *d;
};

int main() {
    std::string line;
    Node *start, *end;

    Node *current_line;
    std::vector<Node*> nodes;

    int y = 0;
    int size;

    while (std::getline(std::cin, line)) {
        current_line = new Node[line.size()];
        size = line.size();

        for (int x = 0; x < line.size(); x++) {
            int h;
            if (line.at(x) == 'S') {
                h = 'a' - 'a';
                start = &current_line[x];
            } else if(line.at(x) == 'E') {
                h = 'z' - 'a';
                current_line[x].is_end = true;
                end = &current_line[x];
            } else {
                h = line.at(x) - 'a';
            }
            current_line[x].x = x;
            current_line[x].y = y;
            current_line[x].height = h;
        }

        y++;
        nodes.push_back(current_line);
    }

    for (y = 0; y < nodes.size(); y++) {
        current_line = nodes.at(y);

        for (int x = 0; x < size; x++) {
            Node &n = current_line[x];
            if (x != 0 && n.is_valid_step(current_line[x - 1])) {
                n.l = &current_line[x - 1];
            }
            if (x != size - 1 && n.is_valid_step(current_line[x + 1])) {
                n.r = &current_line[x + 1];
            }
            if (y != 0 && n.is_valid_step(nodes.at(y - 1)[x])) {
                n.u = &nodes.at(y - 1)[x];
            }
            if (y != nodes.size() - 1 && n.is_valid_step(nodes.at(y + 1)[x])) {
                n.d = &nodes.at(y + 1)[x];
            }
        }
    }

    bool *visited = new bool[size * nodes.size()];
    std::fill_n(visited, size * nodes.size(), false);
    std::queue<Node*> to_visit;

    to_visit.push(start);

    while(!to_visit.empty()) {
        Node *next = to_visit.front();
        to_visit.pop();

        if (next->is_end) {
            std::cout << next->path << std::endl;
            return 0;
        }

        next->bfs_search(to_visit, visited, size);
    }

    return 0;
}
