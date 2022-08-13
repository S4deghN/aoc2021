#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <vector>

template <typename T>
using Vec = std::vector<T>;

std::unordered_map<char, char> pair = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
    {'<', '>'},
};

std::unordered_map<char, int> e_score = {
    {')', 3    },
    {']', 57   },
    {'}', 1197 },
    {'>', 25137},
};

std::unordered_map<char, int> c_score = {
    {')', 1},
    {']', 2},
    {'}', 3},
    {'>', 4},
};

int main() {
    std::fstream file("input", std::ios::in);

    Vec<char> errors;
    Vec<std::string> comps;
    for (std::string line; std::getline(file, line);) {
        Vec<char> expect;
        bool err = false;
        for (auto c : line) {
            if (pair.count(c)) {  //contains() is not available in c++11
                expect.push_back(pair[c]);
            } else {
                if (c == expect.back()) {
                    expect.pop_back();
                } else {
                    errors.push_back(c);
                    err = true;
                    break;
                }
            }
        }

        if (!expect.empty() && !err) {
            std::string comp;
            std::transform(expect.rbegin(), expect.rend(), std::back_inserter(comp),
                           [](auto i) { return i; });
            comps.push_back(comp);
        }
    }

    fmt::print("{}\n", errors);
    fmt::print("{}\n",
               std::accumulate(errors.begin(), errors.end(), 0,
                               [](int acc, const auto& i) { return acc + e_score[i]; }));

    Vec<uint64_t> comp_scors;
    std::transform(comps.begin(), comps.end(), std::back_inserter(comp_scors),
                   [](const auto& str) {
                       return std::accumulate(
                           str.begin(), str.end(), (uint64_t)0,
                           [](auto acc, const auto& c) { return acc * 5 + c_score[c]; });
                   });

    std::sort(comp_scors.begin(), comp_scors.end());
    fmt::print("{}\n", comp_scors[comp_scors.size() / 2]);
}
