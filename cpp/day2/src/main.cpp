#include <cstdint>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    const char filename[] = "input";
    std::fstream s(filename, std::ios::in);

    if (!s.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        std::cout << "successfully opened the file\n";

        std::string dir;
        int val;
        int hor = 0, ver = 0, aim = 0;
        while (s >> dir >> val) {
            if (dir == "forward") {
                hor += val;
                ver += aim * val;
            } else if (dir == "down") {
                aim += val;
            } else if (dir == "up") {
                aim -= val;
            } else {
                std::cout << "err: "
                          << "dir=" << dir << " val=" << val << "\n";
            }
        }
        std::cout << "hor: " << hor << " ver: " << ver << " mul: " << hor * ver
                  << "\n";
    }
}
