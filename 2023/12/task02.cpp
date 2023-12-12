#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <unordered_map>


struct key {
        key(int _vcount, int _all, int _in) {
                vcount = _vcount;
                all = _all;
                in = _in;
        }
        int vcount;
        int all;
        bool in;
};

struct key_hash
{
    std::size_t operator()(const key& k) const
    {
        return
                std::hash<int>()(k.vcount) ^
                (std::hash<int>()(k.all) << 1) ^
                (std::hash<bool>()(k.in) << 2);
    }
};
 
struct key_equal
{
    bool operator()(const key& lhs, const key& rhs) const
    {
        return lhs.vcount == rhs.vcount && lhs.all == rhs.all && lhs.in == rhs.in;
    }
};


using key_map = std::unordered_map<key, long, key_hash, key_equal>;

long try_valid(int *vals, int *groups, int vcount, int gcount, int all, bool in, key_map &visited) {
    if (vcount == 0) {
        if (gcount == 0) {
            return 1;
        }
        if (in && gcount == 1 && groups[0] == 0) {
            return 1;
        }
        return 0;
    }
    
    auto f = visited.find(key(vcount, all, in));
    if (f != visited.end()) {
            return f->second;
    }

    long valid = 0;
    if(vals[0] == '.' || vals[0] == '?') {
        if (in) {
            if (groups[0] == 0) {
                valid += try_valid(vals + 1, groups + 1, vcount - 1, gcount - 1, all, false, visited);
            }
        } else {
            valid += try_valid(vals + 1, groups, vcount - 1, gcount, all, false, visited);
        }
    }

    if(vals[0] == '#' || vals[0] == '?') {
        if (in) {
            if (groups[0] > 0) {
                groups[0]--;
                valid += try_valid(vals + 1, groups, vcount - 1, gcount, all - 1, true, visited);
                groups[0]++;
            }
        } else {
            if (gcount > 0) {
                groups[0]--;
                valid += try_valid(vals + 1, groups, vcount - 1, gcount, all - 1, true, visited);
                groups[0]++;
            }
        }
    }
    visited[key(vcount, all, in)] = valid;
    return valid;
}

int main() {
    std::string line;
    long sum = 0;
    // int progress = 1;

    while (std::getline(std::cin, line)) {
        int i = 0;
        int *vals = new int[(line.size() + 1) * 5];
        int *groups = new int[line.size() * 5];
        int vcount;
        int gcount;
        int group = 0;
        int idx = 0;
        int all = 0;
        key_map visited;

        for (; line.at(i) != ' '; i++) {
            vals[i] = line.at(i);
        }
        vcount = i;
        for (++i; i < line.size(); i++) {
            int c = line.at(i);
            if (c >= '0' && c <= '9') {
                group = group * 10 + c - '0';
            } else {
                groups[idx++] = group;
                all += group;
                group = 0;
            }
        }
        groups[idx++] = group;
        all += group;
        gcount = idx;

        for (i = 1; i < 5; i++) {
            vals[i * (vcount + 1) - 1] = '?';
            memcpy(vals + i * (vcount + 1), vals, vcount * sizeof(int));
            memcpy(groups + i * gcount, groups, gcount * sizeof(int));
        }

        long valid = try_valid(vals, groups, 5 * (vcount + 1) - 1, 5 * gcount, all, false, visited);

        // std::cout << progress++ << valid << std::endl;
        sum += valid;

        delete [] groups;
        delete [] vals;
    }

    std::cout << sum << std::endl;
    return 0;
}
