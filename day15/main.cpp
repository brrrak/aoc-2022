#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

constexpr int g_tuning{4'000'000};

struct Sensor {
    int s_x{}, s_y{}, b_x{}, b_y{}, dist{};
};

int get_dist_to_beacon(const int s_x, const int s_y, const int b_x, const int b_y) {
    return abs(b_x - s_x) + abs(b_y - s_y);
}

std::vector<Sensor> parse_input(std::string filename) {
    std::vector<Sensor> sensors{};
    FILE* fp = fopen(filename.c_str(), "r");
    while (!feof(fp)) {
        int s_x{}, s_y{}, b_x{}, b_y{};
        int input_read{fscanf(fp,
                              "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n",
                              &s_x, &s_y, &b_x, &b_y)};
        if (input_read < 4) {
            continue;
        }
        int dist{get_dist_to_beacon(s_x, s_y, b_x, b_y)};
        sensors.push_back(Sensor{s_x, s_y, b_x, b_y, dist});
    }

    return sensors;
}

std::vector<std::pair<int, int>> merge_ranges(const std::vector<std::pair<int, int>>& ranges) {
    if (ranges.empty()) {
        return {};
    }

    std::vector<std::pair<int, int>> merged;
    merged.reserve(ranges.size());
    merged.push_back(ranges[0]);

    for (size_t i{1}; i < ranges.size(); ++i) {
        if (ranges[i].first - 1 <= merged.back().second) {
            merged.back().second = std::max(merged.back().second, ranges[i].second);
        } else {
            merged.push_back(ranges[i]);
        }
    }

    return merged;
}

int solve_part1(const std::vector<Sensor>& sensors, const int target_y) {
    std::vector<std::pair<int, int>> ranges;
    ranges.reserve(sensors.size());

    for (const Sensor& s : sensors) {
        int lateral_movement_range = s.dist - std::abs(target_y - s.s_y);
        if (lateral_movement_range < 0) {
            continue;
        }

        int left = s.s_x - lateral_movement_range;
        int right = s.s_x + lateral_movement_range;
        if (s.b_y == target_y) {
            if (s.b_x > s.s_x) {
                right -= 1;
            } else if (s.b_x < s.s_x) {
                left += 1;
            } else {
                continue;
            }
        }
        ranges.push_back(std::make_pair(left, right));
    }

    std::sort(ranges.begin(), ranges.end());
    ranges = merge_ranges(ranges);

    int result = 0;
    for (const auto& range : ranges) {
        result += range.second - range.first + 1;
    }
    return result;
}

int get_distress_beacon(const std::vector<Sensor>& sensors, const int target_y) {
    std::vector<std::pair<int, int>> ranges;
    ranges.reserve(sensors.size());

    for (const Sensor& s : sensors) {
        int lateral_movement_range = s.dist - std::abs(target_y - s.s_y);
        if (lateral_movement_range < 0) {
            continue;
        }

        int left = std::max(0, s.s_x - lateral_movement_range);
        int right = std::min(s.s_x + lateral_movement_range, g_tuning);
        ranges.push_back(std::make_pair(left, right));
    }

    std::sort(ranges.begin(), ranges.end());
    ranges = merge_ranges(ranges);

    int result{-1};
    if (ranges.size() > 1) {
        result = ranges[0].second + 1;
    }
    return result;
}

int64_t solve_part2(const std::vector<Sensor>& sensors, const int target_y) {
    int coord_range{target_y * 2};
    int x{}, y{};
    for (; y <= coord_range; ++y) {
        x = get_distress_beacon(sensors, y);
        if (x != -1) break;
    }

    return static_cast<int64_t>(x) * static_cast<int64_t>(g_tuning) + static_cast<int64_t>(y);
}

int main() {
    const int target_y = 2'000'000;
    std::vector<Sensor> sensors{parse_input("input.txt")};

    auto start = std::chrono::high_resolution_clock::now();
    int result1{solve_part1(sensors, target_y)};
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Part 1 Answer: " << result1 << '\n';
    std::cout << "Part 1 took: " << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    int64_t result2{solve_part2(sensors, target_y)};
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Part 2 Answer: " << result2 << '\n';
    std::cout << "Part 2 took: " << duration.count() << " ms\n";

    return 0;
}