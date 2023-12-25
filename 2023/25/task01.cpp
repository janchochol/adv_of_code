#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <set>
#include <limits>

// Copy & Paste from with small modifications https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
int stoer_wagner(std::vector<std::vector<int>>& mat) {
    std::pair<int, std::vector<int>> best = { std::numeric_limits<int>::max() , {} };
    int n = mat.size();
    std::vector<std::vector<int>> co(n);

    for (int i = 0; i < n; i++) {
        co[i] = { i };
    }

    for (int ph = 1; ph < n; ph++) {
        std::vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
            w[t] = std::numeric_limits<int>::min();
            s = t, t = max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = min(best, { w[t] - mat[t][t], co[t] });
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = std::numeric_limits<int>::min();
    }

    return best.second.size();
};


int main(int argc, char *argv[]) {
    std::string line;
    std::unordered_map<std::string, std::set<std::string>> map;
    std::unordered_map<std::string, int> mapping;

    while (std::getline(std::cin, line)) {
        std::string a = line.substr(0, 3);

        for(int i = 5; i < line.size(); i += 4) {
            std::string b = line.substr(i, 3);
            map[a].emplace(b);
            map[b].emplace(a);
        }
    }

    int i = 0;
    for (const auto& [k, v]: map) {
        mapping[k] = i++;
    }

	std::vector<std::vector<int>> adj(mapping.size(), std::vector<int>(mapping.size(), 0));
	for (const auto& [a, neigh]: map) {
	    for (const std::string& b: neigh) {
    		adj[mapping[a]][mapping[b]] = 1;
        }
    }
	int size = stoer_wagner(adj);

    std::cout << (size * (map.size() - size)) << std::endl;

    return 0;
}
