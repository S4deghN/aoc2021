#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#define days 256
#define TASK_1

size_t crab_fuel() {
    std::fstream file("input");
    std::vector<int> positions;
    size_t pos_sum = 0;
    for (int num; file >> num;) {
        pos_sum += num;
        positions.push_back(num);
        file.ignore();
    }
    size_t pos_count = positions.size();
#if defined TASK_2
    int best_pos_1 = pos_sum / pos_count;
    int best_pos_2 = pos_sum / pos_count + 1;
    size_t best_sum_1 = 0;
    size_t best_sum_2 = 0;
    for (size_t i = 0; i < pos_count; ++i) {
        best_sum_1 += ((std::abs(best_pos_1 - positions[i]) + 1) *
                       std::abs(best_pos_1 - positions[i])) /
                      2;
        best_sum_2 += ((std::abs(best_pos_2 - positions[i]) + 1) *
                       std::abs(best_pos_2 - positions[i])) /
                      2;
    }
    int sum_res = std::min(best_sum_1, best_sum_2);
#elif defined TASK_1
    std::sort(positions.begin(), positions.end());
    size_t sum_res = pos_sum;
    for (size_t i = 0; i < pos_count / 2; ++i) {
        sum_res -= 2 * positions[i];
    }
#endif
    return sum_res;
}

template <typename T> void part1(std::vector<T>& positions) {

    std::sort(positions.begin(), positions.end());
    int median = positions.at((positions.size() + 1) / 2);

    int fuel = 0;
    for (auto pos : positions) {
        fuel += std::abs(pos - median);
    }

    fmt::print("{}\n", median);
    fmt::print("{}\n", fuel);
}

template <typename T> void part2(std::vector<T>& positions) {
    int average = (std::accumulate(positions.begin(), positions.end(), 0) + 1) /
                  positions.size();

    int fuel = 0;
    for (auto pos : positions) {
        int dist = std::abs(pos - average);
        for (int i = 1; i <= dist; ++i) {
            fuel += i;
        }
    }
    fmt::print("{}\n", average);
    fmt::print("{}\n", fuel);
}

int main() {
    // read the file
    std::fstream s("input", std::ios::in);

    std::vector<int> positions;
    for (int item; s >> item;) {
        s.ignore(); // discard the ','
        positions.push_back(item);
    }

    part1(positions);
    part2(positions);
}
