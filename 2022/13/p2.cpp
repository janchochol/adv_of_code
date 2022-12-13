#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

class DListItem {
public:
    virtual void dump()  = 0;
    virtual int is_left(DListItem *right) = 0;
};

class DList : public DListItem {
public:
    DList(std::vector<DListItem*> &list) : list(list) { }

    void dump() {
        std::cout << "[";
        for (DListItem *i : list) {
            i->dump();
            std::cout << ",";
        }
        std::cout << "]";
    }

    int is_left(DListItem *right);

    std::vector<DListItem*> list;
};

class DInt : public DListItem {
public:
    DInt(int value) : value(value) { }

    void dump() {
        std::cout << value;
    }

    int is_left(DListItem *right) {
        DInt *right_int = dynamic_cast<DInt*>(right);

        if (right_int != NULL) {
            // std::cout << "I: " << value << ":" << right_int->value << std::endl;
            if (value < right_int->value) {
                return 1;
            } else if(value > right_int->value) {
                return -1;
            } else {
                return 0;
            }
        } else {
            std::vector<DListItem*> temp;

            temp.push_back(this);

            DList list(temp);

            return list.is_left(right);
        }
    }

    int value;
};

int DList::is_left(DListItem *right) {
    DList *right_list = dynamic_cast<DList*>(right);

    if (right_list != NULL) {
        int i;

        // std::cout << "S" << std::endl;
        for (i = 0; i < list.size(); i++) {
            // std::cout << "C: " << i << std::endl;
            if (i >= right_list->list.size()) {
                // std::cout << "E: right EOF" << std::endl;
                return -1;
            }
            int sub = list.at(i)->is_left(right_list->list.at(i));

            if (sub != 0) {
                // std::cout << "E: sub " << sub << std::endl;
                return sub;
            }
        }
        if (i < right_list->list.size()) {
            // std::cout << "E: left EOF" << std::endl;
            return 1;
        } else {
            // std::cout << "E: same" << std::endl;
            return 0;
        }
    } else {
        std::vector<DListItem*> temp;

        temp.push_back(right);

        DList tlist(temp);

        return is_left(&tlist);
    }
    return 0;
}

DListItem *parse(std::string &line, int &position) {
    DListItem *ret;

    if (line.at(position) == '[') {
        std::vector<DListItem*> list;

        position++;
        while(line.at(position) != ']') {
            list.push_back(parse(line, position));
            if (line.at(position) == ',') {
                position++;
            }
        }
        position++;
        ret = new DList(list);
    } else {
        int len = 1;
        while (line.at(position + len) >= '0' && line.at(position + len) <= '9') {
            len++;
        }
        ret = new DInt(stoi(line.substr(position, len)));
        position += len;
    }
    return ret;
}

bool compare(DListItem *a, DListItem *b) {
    return a->is_left(b) == 1;
}

int main() {
    std::string line;
    int position = 0;
    int sum = 1;

    std::vector<DListItem*> packets;

    while (std::getline(std::cin, line)) {
        position = 0;
        DListItem *left = parse(line, position);

        std::getline(std::cin, line);
        position = 0;
        DListItem *right = parse(line, position);

        packets.push_back(left);
        packets.push_back(right);

        std::getline(std::cin, line);
    }

    sort(packets.begin(), packets.end(), compare);

    position = 0;
    line = "[[2]]";
    DListItem *div1 = parse(line, position);
    position = 0;
    line = "[[6]]";
    DListItem *div2 = parse(line, position);

    int st = 0;

    for (int i = 0; i < packets.size(); i++) {
        packets.at(i)->dump();
        std::cout << std::endl;

        if (st == 0) {
            if (div1->is_left(packets.at(i)) == 1) {
                st++;
                sum *= (i + 1);
                }
        }
        if (st == 1) {
            if (div2->is_left(packets.at(i)) == 1) {
                sum *= (i + 2);
                st++;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
