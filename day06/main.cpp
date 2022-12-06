#include <fstream>
#include <iostream>
#include <unordered_map>

bool is_marker(const std::unordered_map<char, int>& map) {
    for (auto const pair : map) {
        if (pair.second > 1) {
            return false;
        }
    }
    return true;
}

void solve(std::ifstream& fin, const unsigned long n) {
    while (fin) {
        std::string line;
        getline(fin, line);
        if (line.length() < n)
            continue;

        std::unordered_map<char, int> counter;
        unsigned long i{0};
        for (; i < n; ++i) {
            counter.try_emplace(line[i], 0);
            ++counter[line[i]];
        }
        if (is_marker(counter)) {
            std::cout << "First marker after character: " << i << '\n';
            continue;
        }

        for (; i < line.length(); ++i) {
            if (--counter[line[i - n]] < 1)
                counter.erase(line[i - n]);
            if (counter.count(line[i]) == 0)
                counter.try_emplace(line[i], 0);
            ++counter[line[i]];
            if (counter.size() == n) {
                std::cout << "First marker after character: " << i + 1 << '\n';
                break;
            }
        }

        if (i == line.length())
            std::cout << "Unable to find start-of-message marker!\n";
    }
}

int main() {
    std::ifstream fin("input.txt");

    std::cout << "----------------------- Part 1 -----------------------\n"; 
    solve(fin, 4);

    std::cout << "----------------------- Part 2 -----------------------\n"; 
    fin.clear();
    fin.seekg(0);
    solve(fin, 14);

    fin.close();

    return 0;
}