#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <list>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Not sure how it works.
std::vector<std::string> split(const std::string str,
                               const std::string regex_str) {
    std::regex regexz(regex_str);
    std::vector<std::string> list(
        std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
        std::sregex_token_iterator());
    return list;
}

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

struct Num {
    Num(int num) : num{num} {}
    int num = 0;
    bool mark = 0;
};

#define TABLESIZE

int main() {
    // read the file
    std::fstream s("testInput", std::ios::in);

    // get the rolls
    std::string rolls_string;
    std::getline(s, rolls_string);
    std::istringstream rolls_stream(rolls_string);
    std::vector<int> rolls;
    for (std::string item; std::getline(rolls_stream, item, ',');) {
        rolls.push_back(std::stoi(item));
    }
    // for (int item; rolls_stream >> item;) {
    //     // read the ','. >>-ing a non numeric or whitespace into an integer
    //     // returns error
    //     rolls_stream.get();
    //     rolls.push_back(item);
    // }

    fmt::print("{}\n", rolls);

    // extract the table numbers and put them into a singe flat_table
    std::deque<Num> flat_table;
    // both methods work, I didn't know I can use the second method so I wrote
    // the first one
    // for (std::string item; s >> item;) {
    //     if (!item.empty()) {
    //         flat_table.emplace_back(Num(std::stoi(item)));
    //     }
    // }

    for (int item; s >> item;) {
        flat_table.emplace_back(Num(item));
    }

    // game loop
    int winner_score = 0;
    for (auto roll : rolls) {

        // check for num and mark it, if it matches the roll
        for (int i = 0; i < flat_table.size(); i += 25) {
            for (int j = 0; j < 25; j++) {
                int idx = i + j;
                if (flat_table[idx].num == roll) {
                    flat_table[idx].mark = true;
                    break;
                }
            }
        }

        //check for row win condition
        for (int i = 0; i < flat_table.size(); i += 25) {
            for (int j = 0; j < 25; j += 5) {
                int row_sum = 0;
                for (int k = 0; k < 5; k += 1) {
                    int idx = i + j + k;
                    row_sum += flat_table[idx].mark;
                    if (row_sum == 5) {
                        if (flat_table.size() == 25) {
                            for (int s = 0; s < 0 + 25; s++) {
                                winner_score +=
                                    flat_table[s].mark ? 0 : flat_table[s].num;
                            }
                            winner_score *= roll;
                            goto gameloopend;
                        }
                        flat_table.erase(flat_table.begin() + i,
                                         flat_table.begin() + i + 25);
                        i -= 25;
                    }
                }
            }
        }

        //check for column win condition
        for (int i = 0; i < flat_table.size(); i += 25) {
            for (int k = 0; k < 5; k += 1) {
                int col_sum = 0;
                for (int j = 0; j < 25; j += 5) {
                    int idx = i + j + k;
                    col_sum += flat_table[idx].mark;
                    if (col_sum == 5) {
                        if (flat_table.size() == 25) {
                            for (int s = 0; s < 0 + 25; s++) {
                                winner_score +=
                                    flat_table[s].mark ? 0 : flat_table[s].num;
                            }
                            winner_score *= roll;
                            goto gameloopend;
                        }
                        flat_table.erase(flat_table.begin() + i,
                                         flat_table.begin() + i + 25);
                        i -= 25;
                    }
                }
            }
        }
    }
gameloopend:

    // print tables
    for (int i = 0; i < flat_table.size(); i += 25) {
        for (int j = 0; j < 25; j += 5) {
            for (int k = 0; k < 5; k += 1) {
                int idx = i + j + k;
                fmt::print(flat_table[idx].mark ? fmt::emphasis::bold
                                                : fmt::emphasis::faint,
                           "{:>2} ", flat_table[idx].num);
            }
            fmt::print("\n");
        }
        fmt::print("\n");
    }

    fmt::print("Winner's score: {}\n", winner_score);
}
