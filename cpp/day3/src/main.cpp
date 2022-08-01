#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

template <typename std::size_t size>
int32_t arrToint32(std::array<bool, size>& arr) {
    if (size > 32) {
        return 0;
    }

    int32_t ret = 0;
    for (auto num : arr) {
        ret = ret << 1 | num;
    }
    return ret;
}

enum Rule {
    MoreCommon = 0,
    LessCommon = 1
};

std::string reduceDiagnos(std::deque<std::string> lines, Rule rule) {
    for (int i = 0; i < 12; i++) {
        char common = 0;
        int common_count = 0;

        for (auto line : lines) {
            common_count += line[i] == '1' ? 1 : 0;
        }

        if (lines.size() == 1)
            break;

        common = ((common_count >= (lines.size() + 1) / 2) ^ rule) ? '1' : '0';

        for (int j = 0; j < lines.size(); j++) {
            std::string line = lines[j];
            if (line[i] != common) {
                lines.erase(lines.begin() + j);
                j--;
            }
        }
    }
    return lines[0];
}

int main() {
    std::fstream s("input", std::ios::in);
    std::deque<std::string> lines;
    for (std::string line; s >> line;) {
        lines.emplace_back(line);
    }

    std::string O2  = reduceDiagnos(lines, MoreCommon);
    std::string CO2 = reduceDiagnos(lines, LessCommon);

    fmt::print("{}\n", O2);
    fmt::print("{}\n", CO2);
    fmt::print("Answere: {}", std::stoi(O2, NULL, 2) * std::stoi(CO2, NULL, 2));
}
