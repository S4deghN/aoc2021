#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

auto around(const std::pair<int, int> point) {
    return std::list<std::pair<int, int>>{
        {point.first,     point.second + 1},
        {point.first + 1, point.second    },
        {point.first - 1, point.second    },
        {point.first,     point.second - 1}
    };
}

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 31 + v.second;
    }
};

int main() {
    std::fstream file("testInput", std::ios::in);

    std::deque<std::deque<int>> table;
    std::deque<int> row;
    for (char c; file.get(c);) {
        row.emplace_back(c - '0');
        if (file.peek() == '\n') {
            file.ignore();
            row.push_back(9);
            row.push_front(9);
            table.emplace_back(std::move(row));
        }
    }
    table.emplace_back(std::deque<int>(table[0].size(), 9));
    table.emplace_front(std::deque<int>(table[0].size(), 9));

    int ans = 0;
    std::vector<std::pair<int, int>> anchors;
    for (int i = 1; i < table.size() - 1; i++) {
        for (int j = 1; j < table[0].size() - 1; j++) {
            auto a = around({i, j});
            if (std::all_of(a.begin(), a.end(), [&](auto a) {
                    return table[a.first][a.second] > table[i][j];
                })) {
                ans += table[i][j] + 1;
                anchors.emplace_back(std::pair<int, int>(i, j));
            }
        }
    }

    std::vector<std::vector<int>> basines;
    for (auto point : anchors) {
        std::unordered_set<std::pair<int, int>, pair_hash> visited;
        std::list<std::pair<int, int>> to_visit;

        to_visit.push_back(point);

        std::vector<int> basine;
        while (!to_visit.empty()) {
            auto cord = to_visit.front();
            to_visit.pop_front();

            // visit
            if (table[cord.first][cord.second] != 9 &&
                !visited.contains(cord)) {
                to_visit.splice(to_visit.end(), around(cord));
                visited.insert(cord);
                basine.push_back(table[cord.first][cord.second]);
            }
        }
        basines.emplace_back(std::move(basine));
    }

    for (auto row : table) {
        for (auto n : row) {
            fmt::print(n >= 9 ? fmt::emphasis::bold : fmt::emphasis::faint,
                       "{:>3}", n);
        }
        fmt::print("\n");
    }

    // std::sort(basines.begin(), basines.end(),
    //           [](const auto& a, const auto& b) { return a.size() > b.size(); });

    fmt::print("Answere1: {}\n", ans);
    fmt::print("Anchors: {}\n", anchors);
    fmt::print("basines: {}\n", basines);
    fmt::print("Answere2: {}\n",
               std::accumulate(basines.begin(), basines.begin() + 3, 1,
                               [](int product, const auto& vec) {
                                   return product * vec.size();
                               }));
}
