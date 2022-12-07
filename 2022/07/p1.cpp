#include <iostream>
#include <unordered_map>
#include <string>

class Node {
public:
    Node(Node *parent) : parent(parent) {}

    size_t size;
    Node *parent;
    std::unordered_map<std::string, Node*> children;
};

size_t sum_nice_dirs(Node *dir) {
    size_t sum = 0;
    if (dir->size <= 100000) {
        sum += dir->size;
    }
    for (const std::pair<const std::string, Node*>& curr : dir->children) {
        sum += sum_nice_dirs(curr.second);
    }
    return sum;
}

int main() {
    std::string line;
    bool in_ls = false;

    Node *root = new Node(NULL);
    Node *current = root;

    while (std::getline(std::cin, line)) {
        if (in_ls) {
            if (line.rfind("dir ", 0) == 0) {
                current->children[line.substr(4)] = new Node(current);
            } else if (line.rfind("$ ", 0) == 0) {
                in_ls = false;
            } else {
                Node *to_update = current;

                int end = line.find(" ");
                size_t val = stoi(line.substr(0, end));

                while (to_update) {
                    to_update->size += val;
                    to_update = to_update->parent;
                }
            }
        }
        if (!in_ls) {
            if (line.rfind("$ cd ", 0) == 0) {
                std::string dir = line.substr(5);
                if (dir.compare("/") == 0) {
                    current = root;
                } else if (dir.compare("..") == 0) {
                    current = current->parent;
                } else {
                    current = current->children[dir];
                }
            } else if(line.compare("$ ls") == 0) {
                in_ls = true;
            }
        }
    }
    size_t sum = sum_nice_dirs(root);
    if (root->size <= 100000) {
        sum -= root->size;
    }
    std::cout << sum << std::endl;
    return 0;
}
