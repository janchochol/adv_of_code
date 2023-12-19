#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>

struct part {
    part() {
        ix = 1;
        im = 1;
        ia = 1;
        is = 1;
        ax = 4000;
        am = 4000;
        aa = 4000;
        as = 4000;
        valid = true;
    }

    void dump() const {
        std::cout << "MIN x:" << ix << ",m:" << im << ",a:" << ia << ",s:" << is;
        std::cout << ", MAX x:" << ax << ",m:" << am << ",a:" << aa << ",s:" << as << std::endl;
    }
    
    long count() const {
        long r = 1;
        r *= ax - ix + 1;
        r *= am - im + 1;
        r *= aa - ia + 1;
        r *= as - is + 1;
        return r;
    }

    bool valid;
    int ix, im, ia, is;
    int ax, am, aa, as;
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

    void match(const part &p, part& ok, part &ko) const {
        int pivalue;
        int pavalue;
        int *iok, *aok;
        int *iko, *ako;
        switch(check) {
            case 'x':
                pivalue = p.ix;
                pavalue = p.ax;
                iok = &ok.ix;
                aok = &ok.ax;
                iko = &ko.ix;
                ako = &ko.ax;
                break;
            case 'm':
                pivalue = p.im;
                pavalue = p.am;
                iok = &ok.im;
                aok = &ok.am;
                iko = &ko.im;
                ako = &ko.am;
                break;
            case 'a':
                pivalue = p.ia;
                pavalue = p.aa;
                iok = &ok.ia;
                aok = &ok.aa;
                iko = &ko.ia;
                ako = &ko.aa;
                break;
            case 's':
                pivalue = p.is;
                pavalue = p.as;
                iok = &ok.is;
                aok = &ok.as;
                iko = &ko.is;
                ako = &ko.as;
                break;
        }
        // std::cout << " (" << pvalue << cond << value << ") ";
        switch(cond) {
            case '<':
                if (pavalue < value) {
                    ko.valid = false;
                } else if (pivalue >= value) {
                    ok.valid = false;
                } else {
                    *aok = value - 1;
                    *iko = value;
                }
                break;
            case '>':
                if (pivalue > value) {
                    ko.valid = false;
                } else if (pavalue <= value) {
                    ok.valid = false;
                } else {
                    *iok = value + 1;
                    *ako = value;
                }
                break;
        }
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

long flow(const std::unordered_map<std::string, workflow> &workflows, const std::vector<part>& parts, const std::string& name) {
    if (name == "A") {
        long r = 0;
        for (const auto& p: parts) {
            r += p.count();
        }
        return r;
    } else if (name == "R") {
        return 0;
    }

    // std::cout << "W: " << name << std::endl;
    const auto &w = workflows.find(name);
    std::vector<part> process = parts;
    std::vector<part> rems;
    long ret = 0;

    for (const rule& r : w->second.rules) {
        std::vector<part> oks;

        // r.dump();
        for (const auto& p: process) {
            part ok = p;
            part ko = p;
            r.match(p, ok, ko);
            if (ok.valid) {
                oks.push_back(ok);
            }
            if (ko.valid) {
                rems.push_back(ko);
            }
        }
        if (oks.size() > 0) {
            ret += flow(workflows, oks, r.next);
        }
        process = std::move(rems);
    }
    if (process.size() > 0) {
        ret += flow(workflows, process, w->second.last);
    }
    return ret;
}

int main() {
    std::string line;
    std::unordered_map<std::string, workflow> workflows;

    while (std::getline(std::cin, line)) {
        if (line.size() == 0) {
            break;
        } else  {
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
        }
    }
    std::vector<part> start;
    start.emplace_back();

    long sum = flow(workflows, start, "in");

    std::cout << sum << std::endl;

    return 0;
}
