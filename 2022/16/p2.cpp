#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

struct Valve {
    Valve() : id(0), rate(0), next(NULL), node_id(-1) {}

    Valve(int id) : id(id), rate(0), next(NULL), node_id(-1) {}

    int id;
    std::string name;
    int rate;
    int next_count;

    int *next;

    int *distances;
    int node_id;
};

int browse_valves(Valve *valves_arr, int *visited_me, int *visited_el, int *visited2, int rem, int curr_me, int curr_el, int time, int value, int tic, int max, int size, int *nodes) {
    if (rem == 0) {
        // std::cout << "RR: " << time << std::endl;
        value += tic * time;
        time = 0;
    }
    if (value > max) {
        max = value;
        std::cout << "Max: " << max << "(" << tic << "," << time << ")" << std::endl;
    }
    if (time < 1) {
        return max;
    }
    if (max > value + (rem + tic) * time) {
        return max;
    }
    // std::cout << "enter: " << valves_arr[curr_me].name << "," << valves_arr[curr_el].name << "(" << value << ")" << std::endl;

    int old_me = visited_me[curr_me];
    int old_el = visited_el[curr_el];

    visited_me[curr_me] = tic;
    visited_el[curr_el] = tic;
    // only move
    for (int i = -1; i < valves_arr[curr_me].next_count; i++) {
        int next_me;
        if (i == -1) {
            if (valves_arr[curr_me].node_id == -1) {
                continue;
            }
            if (time == 1) {
                continue;
            }
            if (visited2[curr_me] == 0) {
                continue;
            }
            visited2[curr_me] = 0;
            next_me = curr_me;

            value += tic;
            rem -= valves_arr[curr_me].rate;
            tic += valves_arr[curr_me].rate;
            visited_me[curr_me] = tic;
            value -= tic;
        } else {
            next_me = valves_arr[curr_me].next[i];
            int p;
            for (p = 0; p < size; p++) {
                if (visited2[nodes[p]] == -1 && valves_arr[curr_me].distances[nodes[p]] == i) {
                    break;
                }
            }
            if (p == size) {
                continue;
            }
        }

        if (i == -1 || visited_me[next_me] < tic) {
            for (int j = -1; j < valves_arr[curr_el].next_count; j++) {
                int next_el;
                if (j == -1) {
                    if (valves_arr[curr_el].node_id == -1) {
                        continue;
                    }
                    if (time == 1 && i != -1) {
                        continue;
                    }
                    if (visited2[curr_el] == 0) {
                        continue;
                    }
                    visited2[curr_el] = 0;
                    next_el = curr_el;

                    value += tic;
                    rem -= valves_arr[curr_el].rate;
                    tic += valves_arr[curr_el].rate;
                    value -= tic;
                    visited_el[curr_el] = tic;
                    if (value > max) {
                        max = value;
                        std::cout << "Max: " << max << std::endl;
                    }
                } else {
                    next_el = valves_arr[curr_el].next[j];
                    int p;
                    for (p = 0; p < size; p++) {
                        if (visited2[nodes[p]] == -1 && valves_arr[curr_el].distances[nodes[p]] == j) {
                            break;
                        }
                    }
                    if (p == size) {
                        continue;
                    }
                }

                if (j == -1 || visited_el[next_el] < tic) {
                    int sub = browse_valves(valves_arr, visited_me, visited_el, visited2, rem, next_me, next_el, time - 1, value + tic, tic, max, size, nodes);

                    if (sub > max) {
                        max = sub;
                    }
                }
                if (j == -1) {
                    value += tic;
                    tic -= valves_arr[curr_el].rate;
                    rem += valves_arr[curr_el].rate;
                    value -= tic;
                    visited_el[curr_el] = tic;
                    visited2[curr_el] = -1;
                }
            }
        }

        if (i == -1) {
            value += tic;
            tic -= valves_arr[curr_me].rate;
            rem += valves_arr[curr_me].rate;
            value -= tic;
            visited_me[curr_me] = tic;
            visited2[curr_me] = -1;
        }
    }

    visited_me[curr_me] = old_me;
    visited_el[curr_el] = old_el;
//    std::cout << "leave: " << valves_arr[curr].name << std::endl;

    return max;
}

struct Node {
    int orig_id;
    int rate;
    int *dists;
};

Valve *valves_arr;
bool *available;
bool *added;
int count;
Node *nodes;
int max;

std::string help[] = { "JJ", "DD", "HH", "BB", "CC", "EE" };
int help_idx = 0;
std::unordered_map<std::string, Valve> valves;

int debug[100];
int debug_act[100];
int debug_depth = 0;

void alg2(int next_me, int time_me, int next_el, int time_el, int time, int value, int tic) {
    int start;
    int elapsed;
    int next_tic;
    int remove;
    bool used = false;

    int onext_me = next_me;
    int otime_me = time_me;
    int onext_el = next_el;
    int otime_el = time_el;

    int next_time_me, next_time_el;
    int next_next_me, next_next_el;

    // std::cout << debug_depth << " Enter " << valves_arr[nodes[next_me].orig_id].name << " " << time_me << " " << valves_arr[nodes[next_el].orig_id].name << " " << time_el << " " << time << " " << value << " " << tic << " " << std::endl;

    if (value > max) {
        max = value;
        std::cout << "Max: " << max << std::endl;
    }

    if (time_me == 0) {
        start = next_me;
    } else {
        start = next_el;
    }
    for (int i = 0; i < count; i++) {
/*        if (help_idx < 6) {
            i = valves[help[help_idx++]].node_id;
        } */
        // std::cout << debug_depth << " XXX " << i << std::endl;
        if (available[i]) {
            used = true;
            // std::cout << "USE " << valves_arr[nodes[i].orig_id].name << std::endl;
            available[i] = false;

            if (time_me == 0) {
                debug_act[debug_depth] = 0;
                next_next_me = i;
                next_next_el = next_el;
                next_time_me = nodes[start].dists[i] + 1;
                next_time_el = time_el;
            } else {
                debug_act[debug_depth] = 1;
                next_next_me = next_me;
                next_next_el = i;
                next_time_me = time_me;
                next_time_el = nodes[start].dists[i] + 1;
            }

            remove = -1;
            next_tic = tic;
            if (next_time_me <= next_time_el) {
                elapsed = next_time_me;
                if (added[next_next_me] == false) {
                    remove = next_next_me;
                    added[remove] = true;
                    // std::cout << "ADD1 " << valves_arr[nodes[next_next_me].orig_id].name << "(" << elapsed << ")" << std::endl;
                    next_tic = tic + nodes[next_next_me].rate;
                }
            } else {
                elapsed = next_time_el;
                if (added[next_next_el] == false) {
                    remove = next_next_el;
                    added[remove] = true;
                    // std::cout << "ADD2 " << valves_arr[nodes[next_next_el].orig_id].name <<  "(" << elapsed << ")" << std::endl;
                    next_tic = tic + nodes[next_next_el].rate;
                }
            }

            if (time < elapsed) {
                int test = value + time * tic;
/*                std::cout << "Value1: " << test << " ";
                for (int d = 0; d < debug_depth; d++) {
                    std::cout << valves_arr[nodes[debug[d]].orig_id].name << "(" << debug_act[d] << ")" << " -> ";
                }
                std::cout << std::endl; */
                if (test > max) {
                    max = test;
                    std::cout << "Max1: " << max << " (" << time << ")" << std::endl;
                }
            } else {
                debug[debug_depth++] = i;
                alg2(next_next_me, next_time_me - elapsed, next_next_el, next_time_el - elapsed, time - elapsed, value + tic * elapsed, next_tic);
                debug_depth--;
            }

            if (remove != -1) {
                added[remove] = false;
                // std::cout << "UNUSE " << valves_arr[nodes[remove].orig_id].name << std::endl;
            }
            available[i] = true;
        }
    }
    if (!used) {
        // std::cout << "XXX" << std::endl;

        next_tic = tic;
        if (added[next_el] == false) {
            next_tic += nodes[next_el].rate;
        }
        int test = value + time_el * tic + (time - time_el) * next_tic;
        /* std::cout << "Value: " << test << " ";
        for (int d = 0; d < debug_depth; d++) {
            std::cout << valves_arr[nodes[debug[d]].orig_id].name << "(" << debug_act[d] << ")" << " -> ";
        }
        std::cout << std::endl; */
        if (test > max) {
            max = test;
            std::cout << "Max3: " << max << " (" << time << ", " << next_tic << ")" << std::endl;
        }
    }

    if (value + time * tic > max) {
        max = value + time * tic;
        std::cout << "Max2: " << max << " (" << time << ", " << tic << ")" << std::endl;
    }

    // std::cout << "Exit " << valves_arr[nodes[onext_me].orig_id].name << " " << otime_me << " " << valves_arr[nodes[onext_el].orig_id].name << " " << otime_el << " " << time << " " << value << " " << tic << " " << std::endl;
}

struct Distance {
    Distance(int id, int distance, int first) : id(id), distance(distance), first(first) {}

    int id;
    int distance;
    int first;
};

int main() {
    std::string line;
    std::unordered_map<int, int> remaining;
    int *visited_me;
    int *visited_el;
    int *visited2;
    int rem = 0;

    int id = 0;
    int node_id = 0;
    while (std::getline(std::cin, line)) {
        int semi = line.find(';');
        int st = semi + 24;

        if (line.at(st - 1) == 's') {
            st++;
        }

        std::string valve = line.substr(6, 2);
        int rate = stoi(line.substr(23, semi - 23));

        if (valves.find(valve) == valves.end()) {
            valves[valve] = Valve(id++);
        }

        rem += rate;
        valves[valve].rate = rate;
        if (rate > 0 || valve.compare("AA") == 0) {
            valves[valve].node_id = node_id++;
        } else {
            valves[valve].node_id = -1;
        }
        valves[valve].name = valve;
        valves[valve].next_count = (line.size() + 2 - st) / 4;

        std::cout << valve << ":" << valves[valve].next_count << " - ";

        valves[valve].next = new int[valves[valve].next_count];
        for (int i = 0; i < valves[valve].next_count; i++) {
            std::string next_valve = line.substr(st + 4 * i, 2);


            if (valves.find(next_valve) == valves.end()) {
                valves[next_valve] = Valve(id++);
            }
            valves[valve].next[i] = valves[next_valve].id;
            std::cout << next_valve << "(" << valves[valve].next[i] << "), ";
        }
        std::cout << std::endl;
    }
    valves_arr = new Valve[id];
    visited_me = new int[id];
    visited_el = new int[id];
    visited2 = new int[id];
    nodes = new Node[node_id];

    std::fill_n(visited_me, id, -1);
    std::fill_n(visited_el, id, -1);
    std::fill_n(visited2, id, -1);

    for (std::pair<std::string, Valve> name_valve : valves) {
        Valve &valve = name_valve.second;

        valve.distances = new int[id];

        if (valve.node_id != -1) {
            nodes[valve.node_id].orig_id = valve.id;
            nodes[valve.node_id].rate = valve.rate;
            nodes[valve.node_id].dists = new int [node_id];
            std::fill_n(nodes[valve.node_id].dists, node_id, -1);
        }
        remaining[valve.id] = valve.rate;
        valves_arr[valve.id] = valve;
    }
    for (int i = 0; i < id; i++) {
        if (valves_arr[i].node_id != -1) {
            std::queue<Distance> to_visit;

            visited_me[i] = 1;
            valves_arr[i].distances[i] = 0;
            to_visit.push(Distance(i, 1, 0));

            nodes[valves_arr[i].node_id].dists[valves_arr[i].node_id] = 0;

            while (!to_visit.empty()) {
                Distance &item = to_visit.front();
                int next = item.id;
                int dist = item.distance;

                for (int j = 0; j < valves_arr[next].next_count; j++) {
                    int neigh = valves_arr[next].next[j];

                    if (visited_me[neigh] == -1) {
                        int first = j;

                        if (dist > 0) {
                            first = item.first;
                        }
                        visited_me[neigh] = 1;
                        if (valves_arr[neigh].node_id != -1) {
                            nodes[valves_arr[i].node_id].dists[valves_arr[neigh].node_id] = dist;
                        }
                        to_visit.push(Distance(neigh, dist + 1, first));
                    }
                }

                to_visit.pop();
            }
            std::fill_n(visited_me, id, -1);
        }
    }
    count = node_id;
    max = 0;
    available = new bool[count];
    added = new bool[count];

    std::fill_n(available, count, true);
    std::fill_n(added, count, false);

    for (int i = 0; i < count; i++) {
        std::cout << "XX: " << valves_arr[nodes[i].orig_id].name << std::endl;
        for (int j = 0; j < count; j++) {
            std::cout << " -> " << valves_arr[nodes[j].orig_id].name << ": " << nodes[i].dists[j] << std::endl;
        }
    }

    available[valves["AA"].node_id] = false;
    added[valves["AA"].node_id] = true;

    alg2(valves["AA"].node_id, 0, valves["AA"].node_id, 0, 26, 0, 0);

    return 0;
}
