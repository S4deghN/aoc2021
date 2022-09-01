#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <deque>
#include <fstream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

struct Cave {
    std::string name;
    int visit_count = 0;
    bool is_lower = std::islower(name[0]);
    std::set<std::string> conns;
};

void add_cave_from_line(std::map<std::string, Cave>& caves, std::string& line) {
    const auto idx = line.find('-');
    const auto s = line.substr(0, idx);
    const auto e = line.substr(idx + 1);

    if (caves.count(s) == 0) {
        caves.emplace(s, Cave{.name = s});
    }

    if (caves.count(e) == 0) {
        caves.emplace(e, Cave{.name = e});
    }

    caves[s].conns.emplace(e);
    caves[e].conns.emplace(s);
}

bool is_walkable(std::map<std::string, Cave>& caves, std::vector<std::string>& stack,
                 const Cave& cave) {
    // firt part
    // return !cave.is_lower || (cave.is_lower && cave.visit_count == 0)

    // second part
    return !cave.is_lower || cave.visit_count == 0 ||
           (cave.visit_count == 1 && cave.name != "start" &&
               std::all_of(stack.begin(), stack.end(), [&caves](const auto cave_name) {
                   Cave& cave = caves[cave_name];
                   return !cave.is_lower || cave.visit_count < 2;
               }));
}

int push_path(std::map<std::string, Cave>& caves, std::vector<std::string>& stack,
                   const std::string& cave_name) {
    Cave& cave = caves[cave_name];

    if (!is_walkable(caves, stack, cave)) {
        return 0;
    }

    if (cave.name == "end") {
        // fmt::print("p: {}\n", stack);
        return 1;
    }

    cave.visit_count += 1;
    stack.push_back(cave.name);

    int acc = std::accumulate(cave.conns.begin(), cave.conns.end(), (int)0,
                                   [&](auto acc, const auto& cave_name) {
                                       return acc + push_path(caves, stack, cave_name);
                                   });
    stack.pop_back();
    cave.visit_count -= 1;
    return acc;
}

int main() {
    std::fstream file("input", std::ios::in);
    if (!file.is_open()) {
        fmt::print("file err!\n");
    }

    std::map<std::string, Cave> caves;
    for (std::string line; file >> line;) {
        add_cave_from_line(caves, line);
    }

    for (auto cave : caves) {
        fmt::print("{} {}: {}\n", cave.second.is_lower, cave.first, cave.second.conns);
    }

    std::vector<std::string> stack;
    stack.reserve(30);
    int path_count = push_path(caves, stack, "start");

    fmt::print("Total pathes: {}\n", path_count);
}
