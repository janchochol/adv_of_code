#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

struct interval_list {
    std::map<long, long> intervals;

    void dump() {
        for (const auto& [from, to]: intervals) {
            std::cout << "(" << from << "-" << to << ") ";
        }
        std::cout << std::endl;
    }

    void add(long from, long to) {
        std::map<long, long>::iterator iter; 

        //   | f    | t -> ignore
        // |-----------|
        iter = intervals.upper_bound(from);
        if (!intervals.empty()) {
            if (iter == intervals.begin()) {
                iter = intervals.end();
            } else {
                --iter;
            }
        }
        if (iter != intervals.end() && iter->second >= to) {
            return;
        }

        // | f           | t
        //    |-| |-|        -> removed
        iter = intervals.lower_bound(from); 
        while (iter != intervals.end() && iter->second <= to) {
            iter = intervals.erase(iter);
        }

        //    | f     | t -> merge
        //          |---|
        iter = intervals.lower_bound(from);
        if (iter != intervals.end() && iter->first <= to + 1) {
            to = iter->second;
            intervals.erase(iter);
        }

        //    | f     | t -> merge
        //  |---|
        iter = intervals.upper_bound(from);
        if (!intervals.empty()) {
            if (iter == intervals.begin()) {
                iter = intervals.end();
            } else {
                --iter;
            }
        }
        if (iter != intervals.end() && iter->second >= from - 1) {
            iter->second = to;
            return;
        }

        intervals[from] = to;
    }

    interval_list remove(long from, long to) {
        std::map<long, long>::iterator iter; 
        interval_list ret;

        //   | f    | t -> ignore
        // |-----------|
        iter = intervals.upper_bound(from);
        if (!intervals.empty()) {
            if (iter == intervals.begin()) {
                iter = intervals.end();
            } else {
                --iter;
            }
        }
        if (iter != intervals.end() && iter->second >= to) {
            long s = iter->second;
            if (iter->first < from) {
                iter->second = from - 1;
            } else {
                intervals.erase(iter);
            }
            if (s > to) {
                intervals[to + 1] = s;
            }
            ret.add(from, to);
            return ret;
        }

        // | f           | t
        //    |-| |-|        -> removed
        iter = intervals.lower_bound(from); 
        while (iter != intervals.end() && iter->second <= to) {
            ret.add(iter->first, iter->second);
            iter = intervals.erase(iter);
        }

        //    | f     | t -> merge
        //          |---|
        iter = intervals.lower_bound(from);
        if (iter != intervals.end() && iter->first <= to) {
            ret.add(iter->first, to);
            long s = iter->second;
            intervals.erase(iter);
            intervals[to + 1] = s;
        }

        //    | f     | t -> merge
        //  |---|
        iter = intervals.upper_bound(from);
        if (!intervals.empty()) {
            if (iter == intervals.begin()) {
                iter = intervals.end();
            } else {
                --iter;
            }
        }
        if (iter != intervals.end() && iter->second >= from) {
            ret.add(from, iter->second);
            iter->second = from - 1;
        }

        return ret;
    }

    void move_to(interval_list& to) {
        std::map<long, long>::iterator iter = intervals.begin();
        while(iter != intervals.end()) {
            to.add(iter->first, iter->second);
            iter = intervals.erase(iter);
        }
    }

    long min() {
        std::map<long, long>::iterator iter;
        iter = intervals.begin();
        if (iter != intervals.end()) {
            return iter->first;
        }
        return 0;
    }
};

int main() {
    std::string line;
    int state = 0;
    interval_list v1;
    interval_list v2;
    interval_list *a = &v1;
    interval_list *b = &v2;

    while (std::getline(std::cin, line)) {
        if (line.length() == 0) {
            continue;
        }
        if (state == 0) {
            long num = 0;
            long numo = 0;
            long idx = 0;
            for (int i = 7; i < line.length() + 1; i++) {
                long c;
                if (i == line.length() || (c = line.at(i)) == ' ') {
                    if (idx & 1) {
                        a->add(numo, numo + num - 1);
                    } else {
                        numo = num;
                    }
                    num = 0;
                    idx++;
                } else {
                    num = 10 * num + c - '0';
                }
            }
            state++;
        } else {
            long s = line.at(0);
            if (s < '0' || s > '9') {
                state++;
                if (state > 2) {
                    a->move_to(*b);
                }
                /* v1.dump();
                   v2.dump(); */
                if (state & 1) {
                    b = &v1;
                    a = &v2;
                } else {
                    a = &v1;
                    b = &v2;
                }
            } else {
                long num = 0;
                long idx = 0;
                long nums[3]; // dest start len
                for (int i = 0; i < line.length() + 1; i++) {
                    long c;
                    if (i == line.length() || (c = line.at(i)) == ' ') {
                        nums[idx] = num;
                        num = 0;
                        idx++;
                    } else {
                        num = 10 * num + c - '0';
                    }
                }
                nums[0] = nums[0] - nums[1];
                nums[2] = nums[1] + nums[2] - 1;
                // shift start end
                interval_list diff = a->remove(nums[1], nums[2]);
                std::map<long, long>::iterator iter = diff.intervals.begin();
                while(iter != diff.intervals.end()) {
                    b->add(iter->first + nums[0], iter->second + nums[0]);
                    ++iter;
                }
            }
        }
    }
    a->move_to(*b);
    std::cout << b->min() << std::endl;
    return 0;
}
