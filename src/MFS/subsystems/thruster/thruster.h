#pragma once

#include <tuple>
#include <map>
#include <climits>
#include <algorithm>

namespace MFS::Subsystems::Thruster {

    inline auto dutyTime = std::map<int, int>{
        {240, 26},
        {250, 20},
        {260, 16},
        {270, 12},
        {280, 10},
        {290, 8},
        {300, 6},
        {600, 0}
    };

    inline auto interpolate = [](std::map<int, int> const& table, int value_x) -> double {
        // O(n), can be optimized by using a sorted set

        int higher_x = INT_MAX;
        int lower_x = INT_MIN;
        int higher_y = 0;
        int lower_y = 0;

        std::for_each(table.begin(), table.end(), [&](auto entry) {
            auto current = entry.first;
            if(current >= value_x) {
                if(current < lower_x) {
                    lower_x = current;
                    lower_y = entry.second;
                }
            } else if(current <= value_x) {
                if(current > higher_x) {
                    higher_x = current;
                    higher_y = entry.second;
                }
            }
        });

        assert(lower_x != INT_MIN && higher_x != INT_MAX);

        return lower_y + value_x*(higher_y - lower_y);
    };

    

    inline auto altitude = 275;
    inline auto currentDutyTime = interpolate(dutyTime, altitude);
}