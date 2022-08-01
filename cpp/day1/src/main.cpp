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

        std::string line;
        int num;
        std::vector<int> vec;
        // the >> operator formats just like << when using
        // cout, therefore since I have only numbers in each I can jus throw
        // my int variable at the output of ">>" and it will just extract
        // the number as an integer before putting it to my variable.
        while (s >> num) {
            vec.push_back(num);
        }

        // loop over the vec and compare the sums
        int pre_sum = INT32_MAX;
        int count = 0;
        for (auto it = vec.begin(); it < vec.end() - 2; it++) {
            int sum = it[0] + it[1] + it[2];
            if (sum > pre_sum) {
                count++;
            }
            pre_sum = sum;
            std::cout << sum << "\n";
        }
        std::cout << "answer: " << count << "\n";
    }
}
