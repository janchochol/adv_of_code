#include <iostream>
#include <string>
#include <queue>
#include <vector>

class Operation {
public:
    virtual int operate(int old) = 0;
    virtual void dump() = 0;
};

class OperationMult : public Operation {
public:
    OperationMult(int mult) : mult(mult) {}

    int operate(int old) {
        return old * mult;
    }

    void dump() {
        std::cout << "* " << mult;
    }

    int mult;
};

class OperationSqrt : public Operation {
public:
    OperationSqrt() {}

    int operate(int old) {
        return old * old;
    }

    void dump() {
        std::cout << "sqrt";
    }
};

class OperationPlus : public Operation {
public:
    OperationPlus(int plus) : plus(plus) {}

    int operate(int old) {
        return old + plus;
    }

    void dump() {
        std::cout << "+ " << plus;
    }

    int plus;
};

class Test {
public:
    virtual int next_monkey(int value) = 0;
    virtual void dump() = 0;
};

class TestDiv : public Test {
public:
    TestDiv(int div, int true_monkey, int false_monkey) : div(div), true_monkey(true_monkey), false_monkey(false_monkey) {}

    int next_monkey(int value) {
        if (value % div ==0) {
            return true_monkey;
        } else {
            return false_monkey;
        }
    }

    void dump() {
        std::cout << "divisable " << div << " ? " << true_monkey << " : " << false_monkey;
    }

    int div;
    int true_monkey;
    int false_monkey;
};


class Monkey {
public:
    Monkey(int idx) : idx(idx), inspections(0) { }

    void dump() {
        std::cout << "Monkey " << idx << std::endl;
        std::cout << " - operation: ";
        oper->dump();
        std::cout << std::endl;
        std::cout << " - test: ";
        test->dump();
        std::cout << std::endl;
        std::cout << " - inspections: " << inspections << std::endl;
        std::cout << " - items: ";

        std::queue<int> t = items;
        while (!t.empty()) {
            std::cout << t.front() << ", ";
            t.pop();
        }
        std::cout << std::endl;
    }

    int inspections;
    int idx;
    Operation *oper;
    Test *test;
    std::queue<int> items;
};

int main() {
    std::string line;
    std::vector<Monkey> monkeys;

    int monkey = 0;

    while (std::getline(std::cin, line)) {
        int current_monkey;

        if (line.substr(0, 6).compare("Monkey") != 0) {
            std::cerr << "Unknown 'Monkey' line: " << line << std::endl;
            return 1;
        }
        current_monkey = stoi(line.substr(7, line.size() - 8));

        if (monkey != current_monkey) {
            std::cerr << "monkey != current_monkey: " << monkey << " != " << current_monkey << std::endl;
            return 1;
        }

        monkeys.push_back(Monkey(monkey));
        Monkey &m = monkeys.at(monkey);

        std::getline(std::cin, line);
        if (line.substr(0, 16).compare("  Starting items") != 0) {
            std::cerr << "Unknown 'Starting items' line: " << line << std::endl;
            return 1;
        }

        int previous = 17;
        int current;

        while (previous < line.size()) {
            current = line.find(',', previous);
            if (current == -1) {
                current = line.size();
            }
            m.items.push(stoi(line.substr(previous + 1, current - previous - 1)));
            previous = current + 1;
        }

        std::getline(std::cin, line);

        if (line.substr(0, 23).compare("  Operation: new = old ") != 0) {
            std::cerr << "Unknown 'Operation' line: " << line << std::endl;
            return 1;
        }

        std::string oper = line.substr(25);
        if (line.at(23) == '+') {
            m.oper = new OperationPlus(stoi(oper));
        } else if(line.at(23) == '*') {
            if (oper.compare("old") == 0) {
                m.oper = new OperationSqrt();
            } else {
                m.oper = new OperationMult(stoi(oper));
            }
        } else {
            std::cerr << "Unknown operatrion: " << line.at(23) << " - " << oper << std::endl;
            return 1;
        }

        std::getline(std::cin, line);

        if (line.substr(0, 20).compare("  Test: divisible by") != 0) {
            std::cerr << "Unknown 'Test' line: " << line << std::endl;
            return 1;
        }

        int div_by = stoi(line.substr(21));

        std::getline(std::cin, line);

        if (line.substr(0, 28).compare("    If true: throw to monkey") != 0) {
            std::cerr << "Unknown 'true monkey' line: " << line << std::endl;
            return 1;
        }
        int true_monkey = stoi(line.substr(29));

        std::getline(std::cin, line);

        if (line.substr(0, 29).compare("    If false: throw to monkey") != 0) {
            std::cerr << "Unknown 'false monkey' line: " << line << std::endl;
            return 1;
        }
        int false_monkey = stoi(line.substr(30));

        m.test = new TestDiv(div_by, true_monkey, false_monkey);

        line = "";
        std::getline(std::cin, line);
        if (line.size() != 0) {
            std::cerr << "Unknown 'end' line: " << line << std::endl;
            return 1;
        }

        m.dump();

        monkey++;
    }

    for (int cycle = 0; cycle < 20; cycle++) {
        for (monkey = 0; monkey < monkeys.size(); monkey++) {
            Monkey &m = monkeys.at(monkey);

            while (!m.items.empty()) {
                int item = m.items.front();

                item = m.oper->operate(item) / 3;
                m.inspections++;
                int next = m.test->next_monkey(item);
                monkeys.at(next).items.push(item);

                m.items.pop();
            }
        }
        std::cout << "After cycle " << cycle << std::endl;
        for (monkey = 0; monkey < monkeys.size(); monkey++) {
            monkeys.at(monkey).dump();
        }
    }
    int max1 = 0;
    int max2 = 0;
    for (monkey = 0; monkey < monkeys.size(); monkey++) {
        Monkey &m = monkeys.at(monkey);

        if (m.inspections > max1) {
            max2 = max1;
            max1 = m.inspections;
        } else if (m.inspections > max2) {
            max2 = m.inspections;
        }
    }

    std::cout << max1 << " * " << max2 << " = " << (max1 * max2) << std::endl;

    return 0;
}
