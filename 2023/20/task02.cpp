#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <numeric>

struct sig {
    sig(const std::string to_, const std::string from_, const bool value_) {
        to = to_;
        from = from_;
        value = value_;
    }
    
    std::string to;
    std::string from;
    bool value;
};

struct mod {
    mod(): type(' ') {
    }

    mod(const char type_, const std::vector<std::string> dests_):
        type(type_),
        dests(dests_),
        state(false)
    {
    }

    void add_input(const std::string name) {
        inputs[name] = false;
    }

    void track(std::unordered_map<std::string, mod>& mods, std::unordered_map<std::string, int>& visited, const std::string& prev) {
        for (const auto& [i, v]: inputs) {
            if (visited.find(i) == visited.end()) {
                std::cout << "V: " << prev << " -> " << i << std::endl;
                visited[i] = 1;
                mods[i].track(mods, visited, i);
            } else {
                std::cout << "V: " << prev << " -> " << i << std::endl;
                visited[i]++;
            }
        }
    }

    void signal(sig &cur, std::queue<sig>& queue) {
        switch(type) {
            case 'b':
                for (const auto& d: dests) {
                    // std::cout << cur.to << ": " << cur.value << " -> " << d << std::endl;
                    queue.emplace(d, cur.to, cur.value);
                }
                break;
            case '%':
                if (cur.value == false) {
                    state = !state;
                    for (const auto& d: dests) {
                        // std::cout << cur.to << ": " << state << " -> " << d << std::endl;
                        queue.emplace(d, cur.to, state);
                    }
                }
                break;
            case '&':
                bool send = false;

                inputs[cur.from] = cur.value;
                for (const auto& [f, i]: inputs) {
                    // std::cout << "FF " << f << " " << i << std::endl;
                    send |= !i;
                }
                for (const auto& d: dests) {
                    // std::cout << cur.to << ": " << send << " -> " << d << std::endl;
                    queue.emplace(d, cur.to, send);
                }
                break;
        }
    }
    
    char type;
    std::vector<std::string> dests;
    bool state;
    std::unordered_map<std::string, bool> inputs;
};

int main() {
    std::string line;
    std::unordered_map<std::string, mod> mods;

    while (std::getline(std::cin, line)) {
        int dests_idx;
        char type;
        std::string name;
        std::vector<std::string> dests;

        if (line.at(0) == 'b') {
            type = 'b';
            dests_idx = 15;
        } else {
            int i;
            type = line.at(0);
            for (i = 1; line.at(i) != ' '; i++) {
            }
            dests_idx = i + 4;
            name = line.substr(1, i - 1);
        }
        
        for (int i = dests_idx; i < line.size(); i++) {
            if (line.at(i) == ',') {
                dests.emplace_back(line.substr(dests_idx, i - dests_idx));
                i += 2;
                dests_idx = i;
            }
        }
        dests.emplace_back(line.substr(dests_idx));
/*        std::cout << "N:" << name << " T:" << type;
        for (const auto& d : dests) {
            std::cout << " D:" << d;
        }
        std::cout << std::endl; */
        if (type == 'b') {
            mods["broadcaster"] = mod('b', dests);
        } else {
            mods[name] = mod(type, dests);
        }
    }

    mods["rx"] = mod();
    mod &rx = mods["rx"];

    for (const auto& [n, m]: mods) {
        for (const auto& d: m.dests) {
            mods[d].add_input(n);
        }
    }
    mod &prev = mods[rx.inputs.begin()->first];
    std::unordered_map<std::string, int> muls;

    // TODO - checks for valid input
    for(int p = 1; true; p++) {
        std::queue<sig> signals;
        int num = 0;

        signals.emplace("broadcaster", "button", false);

        while(!signals.empty()) {
            sig cur_sig = signals.front();
            signals.pop();

            if (cur_sig.value == false && prev.inputs.find(cur_sig.to) != prev.inputs.end()) {
                if (muls.find(cur_sig.to) == muls.end()) {
                    muls[cur_sig.to] = p;
                    if (muls.size() == prev.inputs.size()) {
                        long mul = 1;
                        for (const auto& [i, m]: muls) {
                            mul *= m;
                        }
                        std::cout << mul << std::endl;
                        return 0;
                    }
                }
            }
            mod& cur_mod = mods[cur_sig.to];

            cur_mod.signal(cur_sig, signals);
        }
    }

    return 0;
}
