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

int main() {
    // read the file
    std::fstream s("input", std::ios::in);

    std::array<uint64_t, 9> day = {};
    for (int item; s >> item;) {
        s.get(); // discard the ','
        day[item] += 1;
    }

    for (int i = 0; i < days; i++) {
        uint64_t today = day[0];
        day[0] = 0;
        std::rotate(day.begin(), day.begin() + 1, day.end());
        day[6] += today;
        day[8] += today;
    }

    uint64_t ans = std::accumulate(day.begin(), day.end(), uint64_t(0));
    fmt::print("Answere: {}\n", ans);
}
