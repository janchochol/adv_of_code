#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

struct Valve {
    Valve() : id(0), rate(0), next(NULL) {}

    Valve(int id) : id(id), rate(0), next(NULL) {}

    int id;
    std::string name;
    int rate;
    int next_count;

    int *next;

    int *distances;
};

int browse_valves(Valve *valves_arr, int *visited, int *visited2, int rem, int curr, int time, int value, int tic, int max) {
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
//    std::cout << "enter: " << valves_arr[curr].name << "(" << value << ")" << std::endl;

    int old = visited[curr];

    visited[curr] = tic;
    // only move
    for (int i = 0; i < valves_arr[curr].next_count; i++) {
        int next = valves_arr[curr].next[i];

        // move to only not-opened
        if (visited[next] < tic) {
            int sub = browse_valves(valves_arr, visited, visited2, rem, next, time - 1, value + tic, tic, max);

            if (sub > max) {
                max = sub;
            }
        }
    }

    if (visited2[curr] == -1 && time > 1) {
        visited2[curr] = 1;
        value += tic;
        tic += valves_arr[curr].rate;
        rem -= valves_arr[curr].rate;
        visited[curr] = tic;
        value -= tic;
//        time--;

        int sub = browse_valves(valves_arr, visited, visited2, rem, curr, time - 1, value + tic, tic, max);

        if (sub > max) {
            max = sub;
        }
        // open + move
/*        value += tic;
        tic += valves_arr[curr].rate;
        visited[curr] = tic;
        if (value > max) {
            max = value;
            std::cout << "Max: " << max << std::endl;
        }
        for (int i = 0; i < valves_arr[curr].next_count; i++) {
            int next = valves_arr[curr].next[i];

            if (visited[next] < tic) {
                int sub = browse_valves(valves_arr, visited, visited2, rem - valves_arr[curr].rate, next, time - 2, value + tic, tic, max);

                if (sub > max) {
                    max = sub;
                }
            }
        } */
        value += tic;
        tic -= valves_arr[curr].rate;
        rem += valves_arr[curr].rate;
        value -= tic;

        visited2[curr] = -1;
    }

    visited[curr] = old;
//    std::cout << "leave: " << valves_arr[curr].name << std::endl;

    return max;
}

int main() {
    std::string line;
    std::unordered_map<std::string, Valve> valves;
    std::unordered_map<int, int> remaining;
    Valve *valves_arr;
    int *visited;
    int *visited2;
    int rem = 0;

    int id = 0;
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
    visited = new int[id];
    visited2 = new int[id];

    std::fill_n(visited, id, -1);
    std::fill_n(visited2, id, -1);

    for (std::pair<std::string, Valve> name_valve : valves) {
        Valve &valve = name_valve.second;

        valve.distances = new int[id];

        remaining[valve.id] = valve.rate;
        valves_arr[valve.id] = valve;
    }
/*    for (int i = 0; i < id; i++) {
        std::queue<std::pair<int, int>> to_visit;

        visited[i] = 1;
        valves_arr[i].distances[i] = 0;
        to_visit.push(std::make_pair(i, 0));

        while (!to_visit.empty()) {
            std::pair<int, int> item = to_visit.front();
            int next = item.first;
            int dist = item.second;

            to_visit.pop();

            for (int j = 0; j < valves_arr[next].next_count; j++) {
                int neigh = valves_arr[next].next[j];

                if (visited[neigh] == 0) {
                    visited[neigh] = 1;
                    valves_arr[i].distances[neigh] = dist + 1;
                    to_visit.push(std::make_pair(neigh, dist + 1));
                }
            }

        }
        visited[i] = 0;

    }
*/
    browse_valves(valves_arr, visited, visited2, rem, valves["AA"].id, 30, 0, 0, 0);

    return 0;
}
