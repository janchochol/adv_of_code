#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>

struct part {
    part() {
        x = 0;
        m = 0;
        a = 0;
        s = 0;
    }

    void add(const std::string& line) {
        int *xmas;

        switch(line.at(0)) {
            case 'x':
                xmas = &x;
                break;
            case 'm':
                xmas = &m;
                break;
            case 'a':
                xmas = &a;
                break;
            case 's':
                xmas = &s;
                break;
        }

        for (int i = 2; i < line.size(); i++) {
            *xmas = *xmas * 10 + line.at(i) - '0';
        }
    }
    
    void dump() const {
        std::cout << "x:" << x << ",m:" << m << ",a:" << a << ",s:" << s << std::endl;
    }

    int x, m, a, s;
};


struct rule {
    rule(const std::string& line) {
        check = line.at(0);
        cond = line.at(1);
        value = 0;
        for (int i = 2; i < line.size(); i++) {
            if (line.at(i) == ':') {
                next = line.substr(i + 1);
                break;
            } else {
                value = 10 * value + line.at(i) - '0';
            }
        }
    }

    bool match(const part &p) const {
        int pvalue;
        switch(check) {
            case 'x':
                pvalue = p.x;
                break;
            case 'm':
                pvalue = p.m;
                break;
            case 'a':
                pvalue = p.a;
                break;
            case 's':
                pvalue = p.s;
                break;
        }
        // std::cout << " (" << pvalue << cond << value << ") ";
        switch(cond) {
            case '<':
                return pvalue < value;
            case '>':
                return pvalue > value;
        }
        return false;
    }

    void dump() const {
        std::cout << "C:" << check << ",N:" << cond << ",V:" << value << ",N:" << next;
    }
    char check;
    char cond;
    int value;
    std::string next;
};

struct workflow {
    workflow() {
    }

    workflow(std::vector<rule>&& rules_, std::string&& last_) {
        rules = std::move(rules_);
        last = std::move(last_);
    }

    void dump() const {
        std::cout << "W:";
        for (const rule& r: rules) {
            std::cout << "(";
            r.dump();
            std::cout << ")";
        }
        std::cout << "L:" << last;
    }

    std::vector<rule> rules;
    std::string last;
};

bool flow(const std::unordered_map<std::string, workflow> &workflows, const struct part& p, const std::string& name) {
    if (name == "A") {
        return true;
    } else if (name == "R") {
        return false;
    }

    // std::cout << "W: " << name << std::endl;
    const auto &w = workflows.find(name);

    for (const rule& r : w->second.rules) {
        // r.dump();
        if (r.match(p)) {
            // std::cout << " T" << std::endl;
            return flow(workflows, p, r.next);
        }
        // std::cout << " F" << std::endl;
    }
    return flow(workflows, p, w->second.last);
}

int main() {
    std::string line;
    std::unordered_map<std::string, workflow> workflows;
    bool parts = false;

    long sum = 0;

    while (std::getline(std::cin, line)) {
        if (line.size() == 0) {
            parts = true;
        } else if (!parts) {
            std::vector<rule> rules;
            int state = 0;

            std::string name;
            int rule_start;

            for (int i = 0; i < line.size(); i++) {
                switch(state) {
                    case 0:
                        if (line.at(i) == '{') {
                            name = line.substr(0, i);
                            state = 1;
                            rule_start = i + 1;
                        }
                        break;
                    case 1:
                        if (line.at(i) == ',') {
                            rules.emplace_back(line.substr(rule_start, i - rule_start));
                            rule_start = i + 1;
                        } else if(line.at(i) == '}') {
                            workflows[name] = workflow(std::move(rules), line.substr(rule_start,  i - rule_start));
                        }
                        break;
                }
            }
        } else {
            part p;
            int start = 1;
            for (int i = 1; i < line.size(); i++) {
                if (line.at(i) == ',' || line.at(i) == '}') {
                    p.add(line.substr(start, i - start));
                    start = i + 1;
                }
            }
            // p.dump();
            if(flow(workflows, p, "in")) {
                sum += p.x + p.m + p.a + p.s;
            }
        }
    }
/*    for (const auto [n, w]: workflows) {
        std::cout << n << ":";
        w.dump();
        std::cout << std::endl;
    }
*/
    std::cout << sum << std::endl;

    return 0;
}
