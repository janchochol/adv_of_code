#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <bits/stdc++.h> 

struct card {
    card(char i[5], int t, int s) {
        memcpy(items, i, 5);
        type = t;
        score = s;
    };

    char items[5];
    int type;
    int score;
};

int main() {
    std::string line;
    std::vector<card> cards;

    while (std::getline(std::cin, line)) {
        char items[5];
        int score = 0;

        for (int i = 0; i < 5; i++) {
            char v = 0;
            switch(line.at(i)) {
                case 'A':
                    v = 1;
                    break;
                case 'K':
                    v = 2;
                    break;
                case 'Q':
                    v = 3;
                    break;
                case 'J':
                    v = 4;
                    break;
                case 'T':
                    v = 5;
                    break;
                case '9':
                    v = 6;
                    break;
                case '8':
                    v = 7;
                    break;
                case '7':
                    v = 8;
                    break;
                case '6':
                    v = 9;
                    break;
                case '5':
                    v = 10;
                    break;
                case '4':
                    v = 11;
                    break;
                case '3':
                    v = 12;
                    break;
                case '2':
                    v = 13;
                    break;
            }
            items[i] = v;
        }

        for (int i = 6; i < line.size(); i++) {
            int v;
            switch(line.at(i)) {
            }
            score = score * 10 + line.at(i) - '0';
        }
        int type;
        std::map<int, int> counts;

        for (int i = 0; i < 5; i++) {
            std::map<int, int>::iterator iter = counts.find(items[i]);
            if (iter == counts.end()) {
                counts[items[i]] = 1;
            } else {
                counts[items[i]] = iter->second + 1;
            }
        }
        std::vector<int> values;
        for (std::pair<int, int> iter: counts) {
            values.emplace_back(iter.second);
        }
        std::sort(values.begin(), values.end(), std::greater<int>());

        if (values[0] == 5) {
            // five
            type = 1;
        } else if(values[0] == 4) {
            // four
            type = 2;
        } else if(values[0] == 3 && values[1] == 2) {
            // full house
            type = 3;
        } else if(values[0] == 3) {
            // three
            type = 4;
        } else if(values[0] == 2 && values[1] == 2) {
            // two pairs
            type = 5;
        } else if(values[0] == 2) {
            // pair
            type = 6;
        } else {
            // high
            type = 7;
        }
        cards.emplace_back(items, type, score);
        // std::cout << line << ":" << type << std::endl;
    }
    std::sort(cards.begin(), cards.end(), [](const card &a, const card &b)
            {
                if (a.type != b.type) {
                    return a.type > b.type;
                }
                for (int i = 0; i < 5; i++) {
                    if (a.items[i] != b.items[i]) {
                        return a.items[i] > b.items[i];
                    }
                }
                return true;
            });
    int sum = 0;
    int i = 1;
    for (card &c: cards) {
        sum += c.score * i++;
    }
    std::cout << sum << std::endl;
    return 0;
}

