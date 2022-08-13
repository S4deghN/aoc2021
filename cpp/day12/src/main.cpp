#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
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

    if (!caves.count(s)) {
        caves.emplace(s, Cave{.name = s});
    }

    if (!caves.count(e)) {
        caves.emplace(e, Cave{.name = e});
    }

    caves[s].conns.emplace(e);
    caves[e].conns.emplace(s);


}

bool is_walkable(const Cave& cave) {
    return !cave.is_lower || (cave.is_lower && cave.visit_count == 0);
}

int main() {
    std::fstream file("testInput", std::ios::in);
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
}
