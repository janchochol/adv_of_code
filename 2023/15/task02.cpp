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

struct lens {
    lens(std::string _label, int _val) {
        label = std::move(_label);
        val = _val;
        deleted = false;
    }

    std::string label;
    int val;
    bool deleted;
};

struct box {
    std::vector<lens> lenses;
};

int process(const std::string& label, int op, int value, box *boxes) {
    int box_id = hash(label);

    // std::cout << label << "(" << box_id << "):" << value << " " << op << std::endl;

    if (op == '=') {
        bool found = false;
        for (int i = 0; i < boxes[box_id].lenses.size(); i++) {
            if (boxes[box_id].lenses[i].label == label && boxes[box_id].lenses[i].deleted == false) {
                // std::cout << "chg " << i << std::endl;
                boxes[box_id].lenses[i].val = value;
                found = true;
                break;
            }
        }
        if (!found) {
                boxes[box_id].lenses.emplace_back(label, value);
        }
    } else {
        for (int i = 0; i < boxes[box_id].lenses.size(); i++) {
            if (boxes[box_id].lenses[i].label == label) {
                // std::cout << "del " << i << std::endl;
                boxes[box_id].lenses[i].deleted = true;
            }
        }
    }
    return 0;
}

int main() {
    std::string line;
    
    std::getline(std::cin, line);

    int last = 0;
    int op = 0;
    int value = 0;
    box boxes[256];

    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == '=' || line.at(i) == '-') {
            op = i;
        } else if (line.at(i) == ',') {
            process(line.substr(last, op - last), line.at(op), value, boxes);
            last = i + 1;
            value = 0;
        } else if (line.at(i) >= '0' && line.at(i) <= '9') {
            value = value * 10 + line.at(i) - '0';
        }
    }
    process(line.substr(last, op - last), line.at(op), value, boxes);
    
    long sum = 0;
    for (int i = 0; i < 256; i++) {
        int idx = 1;
        for (int j = 0; j < boxes[i].lenses.size(); j++) {
            if (boxes[i].lenses[j].deleted == false) {
                // std::cout << i << " " << idx << " : " << boxes[i].lenses[j].val << std::endl;
                sum += (i + 1) * idx * boxes[i].lenses[j].val;
                idx++;
            }
        }
    }

    std::cout << sum << std::endl;
    return 0;
}
