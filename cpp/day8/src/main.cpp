#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

//   0:      1:      2:      3:      4:
//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....
//
//  5:      6:      7:      8:      9:
//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg

int main() {
    std::fstream file("input", std::ios::in);

    std::vector<std::vector<std::string>> lines;
    std::vector<std::string> line;
    for (std::string l; file >> l;) {
        std::sort(l.begin(), l.end());
        line.emplace_back(std::move(l));
        if (file.peek() == '\n') {
            std::sort(line.begin(), line.begin() + 10,
                      [](const std::string& first, const std::string& second) {
                          return first.size() < second.size();
                      });
            lines.emplace_back(std::move(line));
        }
    }

    int answere = 0;
    for (auto line : lines) {
        std::map<std::string, int> key;
        std::map<int, std::string> revKey;

        // find the unique ones.
        key[line[0]] = 1;
        revKey[1] = line[0];
        key[line[1]] = 7;
        revKey[7] = line[1];
        key[line[2]] = 4;
        revKey[4] = line[2];
        key[line[9]] = 8;
        revKey[8] = line[9];

        // find 3, 3 is a len5 word that includes 1.
        auto it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 5 &&
                    std::includes(s.begin(), s.end(), revKey[1].begin(),
                                  revKey[1].end());
            });
        key[*it] = 3;
        revKey[3] = *it;

        // find 9, 9 is a len6 word that includes 4.
        it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 6 &&
                    std::includes(s.begin(), s.end(), revKey[4].begin(),
                                  revKey[4].end());
            });
        key[*it] = 9;
        revKey[9] = *it;

        // find 0, 0 is a len6 that includes 1 and is not 9.
        it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 6 && s != revKey[9] &&
                    std::includes(s.begin(), s.end(), revKey[1].begin(),
                                  revKey[1].end());
            });
        key[*it] = 0;
        revKey[0] = *it;

        // find 6, 6 is a len6 that is not 9 or 0.
        it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 6 && s != revKey[9] && s != revKey[0];
            });
        key[*it] = 6;
        revKey[6] = *it;

        // find 5, 5 is a len5 that 9 includes it and it's not a 3.
        it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 5 && s != revKey[3] &&
                    std::includes(revKey[9].begin(), revKey[9].end(), s.begin(),
                                  s.end());
            });
        key[*it] = 5;
        revKey[5] = *it;

        // find 2, 2 is a len5 that is not 5 or 3.
        it = std::find_if(
            line.begin(), line.begin() + 10, [&](const std::string& s) {
                return s.length() == 5 && s != revKey[3] && s != revKey[5];
            });
        key[*it] = 2;
        revKey[2] = *it;

        int sum = 0;
        for (auto it = line.end() - 4; it < line.end(); it++) {
            sum = sum * 10 + key[*it];
        }
        answere += sum;
    }

    fmt::print("ans: {}\n", answere);
}
