#include <fmt/core.h>

#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>

template <typename T>
using Vec = std::vector<T>;

bool is_inbound(const Vec<Vec<int>>& data, int h, int w) {
    return h < data.size() && h >= 0 && w < data[0].size() && w >= 0;
}

bool is_walkable(const Vec<Vec<int>>& data, int h, int w) {
    return is_inbound(data, h, w) && data[h][w] < 9;
}

int walk(Vec<Vec<int>>& data, int h, int w) {
    if (!is_walkable(data, h, w)) {
        return 0;
    }

    data[h][w] = 9;

    Vec<std::pair<int, int>> dirs = {
        {0,  1 },
        {1,  0 },
        {-1, 0 },
        {0,  -1}
    };
    return 1 + std::accumulate(
                   dirs.begin(), dirs.end(), 0, [&](int count, auto& dir) {
                       return count + walk(data, h + dir.first, w + dir.second);
                   });
}

int main() {
    std::fstream file("testInput", std::ios::in);

    Vec<Vec<int>> table;
    Vec<int> row;
    for (char c; file.get(c);) {
        row.emplace_back(c - '0');
        if (file.peek() == '\n') {
            file.ignore();
            table.emplace_back(std::move(row));
        }
    }

    Vec<int> basines;
    for (int h = 0; h < table.size(); ++h) {
        for (int w = 0; w < table[0].size(); ++w) {
            basines.emplace_back(walk(table, h, w));
        }
    }
    std::sort(basines.rbegin(), basines.rend());
    int ans = std::accumulate(basines.begin(), basines.begin() + 3, 1, std::multiplies<>());
    fmt::print("Answere: {}\n", ans);
}
