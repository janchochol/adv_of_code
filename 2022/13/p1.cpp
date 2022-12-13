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

int main() {
    std::string line;
    int idx = 1;
    int sum = 0;

    while (std::getline(std::cin, line)) {
        int position = 0;

        DListItem *left = parse(line, position);

        std::getline(std::cin, line);
        position = 0;
        DListItem *right = parse(line, position);

        left->dump();
        std::cout << std::endl;
        right->dump();
        std::cout << std::endl;
        int v = left->is_left(right);
        std::cout << v << std::endl;
        std::cout << std::endl;

        std::getline(std::cin, line);

        if (v == 1) {
            sum += idx;
        }
        idx++;
    }

    std::cout << sum << std::endl;

    return 0;
}
