#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>

struct Octopus {
    int energy = 0;
    bool flashed = false;
};

template <typename T>
using Vec = std::vector<T>;

Vec<std::pair<int, int>> dirs = {
    {0,  1 },
    {0,  -1},
    {1,  0 },
    {1,  1 },
    {1,  -1},
    {-1, 0 },
    {-1, 1 },
    {-1, -1},
};

bool is_inbound(const Vec<Vec<Octopus>>& table, int h, int w) {
    return h >= 0 && h < table.size() && w >= 0 && w < table[0].size();
}

bool is_flashable(const Vec<Vec<Octopus>>& table, int h, int w) {
    return is_inbound(table, h, w) && !table[h][w].flashed;
}

int gain_energy(Vec<Vec<Octopus>>& table, int h, int w) {
    if (is_flashable(table, h, w) && ++table[h][w].energy > 9) {
        table[h][w].energy = 0;
        table[h][w].flashed = true;
        return 1 +
               std::accumulate(
                   dirs.begin(), dirs.end(), (uint64_t)0, [&](auto acc, const auto& dir) {
                       return acc + gain_energy(table, h + dir.first, w + dir.second);
                   });
    } else {
        return 0;
    }
}

int main() {
    std::fstream file("input", std::ios::in);

    Vec<Vec<Octopus>> table;
    Vec<Octopus> row;
    for (char c; file.get(c);) {
        row.emplace_back(Octopus{c - '0', false});
        if (file.peek() == '\n') {
            file.ignore();
            table.emplace_back(std::move(row));
        }
    }

    Vec<int> flashes;
    int moment;
    for (int i = 0; i < 100; ++i) {
        // go flash
        for (int h = 0; h < table.size(); ++h) {
            for (int w = 0; w < table[0].size(); ++w) {
                flashes.emplace_back(gain_energy(table, h, w));
            }
        }

        // the moment all of the octopuses flash
        if (std::all_of(table.begin(), table.end(), [](const auto& row) {
                return std::all_of(row.begin(), row.end(),
                                   [](const auto& oct) { return oct.flashed; });
            })) {
            moment = i + 1;
            // break;
        }

        // reset flashes
        for (int h = 0; h < table.size(); ++h) {
            for (int w = 0; w < table[0].size(); ++w) {
                table[h][w].flashed = false;
            }
        }
    }

    for (auto row : table) {
        for (auto oct : row) {
            fmt::print("{}", oct.energy);
        }
        fmt::print("\n");
    }

    fmt::print("Flashes: {}\n",
               std::accumulate(flashes.begin(), flashes.end(), (uint64_t)0));
    fmt::print("Moment: {}\n", moment);
}
