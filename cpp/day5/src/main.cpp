#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<int> range(int start, int finish, bool inclusive) {
    int size = std::abs(finish - start);
    if (inclusive) size += 1;

    std::vector<int> range(size, 0);

    if (start < finish) {
        for (int i = 0; i < size; i++) {
            range[i] = start + i;
        }
    } else if (start > finish) {
        for (int i = size - 1; i >= 0; i--) {
            range[i] = start - i;
        }
    }
    return range;
}

struct Pair {
    int x;
    int y;
};

struct Vec {
    Pair a;
    Pair b;
};

int main() {
    // read the file
    std::fstream s("input", std::ios::in);

    std::deque<Pair> pairs;
    std::deque<Vec> vecs;
    size_t table_size = 0;
    for (std::string item; s >> item;) {
        if (std::isdigit(item[0])) {
            char* idx;
            int x = std::strtol(item.c_str(), &idx, 10);

            int y = std::strtol(idx + 1, NULL, 10);
            pairs.emplace_back(Pair{x, y});

            int max = x > y ? x : y;
            table_size = max > table_size ? max : table_size;
        }
        if (pairs.size() == 2) {
            vecs.emplace_back(Vec{pairs[0], pairs[1]});
            pairs.clear();
        }
    }
    for (auto vec : vecs) {
        fmt::print("{},{} -> {},{}\n", vec.a.x, vec.a.y, vec.b.x, vec.b.y);
    }


    // since we the cordinates start from 0, we have to add one to the extracted
    // maximum.
    table_size += 1;
    std::vector<std::vector<int>> table(table_size, std::vector<int>(table_size, 0));

    for (auto vec : vecs) {
        if (vec.a.x == vec.b.x) {
            for (auto i : range(vec.a.y, vec.b.y, true)) {
                table[i][vec.a.x] += 1;
            }
        } else if (vec.a.y == vec.b.y) {
            for (auto j : range(vec.a.x, vec.b.x, true)) {
                table[vec.a.y][j] += 1;
            }
        } else {
            auto i_range = range(vec.a.y, vec.b.y, true);
            auto j_range = range(vec.a.x, vec.b.x, true);
            for (int k = 0; k < i_range.size(); k++) {
                table[i_range[k]][j_range[k]] += 1;
            }
        }
    }

    // print the table
    for (auto row : table) {
        for (auto point : row) {
            if (point > 0)
                fmt::print("{}  ", point);
            else
                fmt::print(".  ");
        }
        fmt::print("\n");
    }

    // calculate answere
    int answere = 0;
    for (auto row : table) {
        for (auto point : row) {
            if (point > 1) {
                answere++;
            }
        }
    }
    fmt::print("Answere: {}\n", answere);
}
