#pragma once
#include <string>
#include <tuple>

namespace rtype_common {
    std::string pack_player(int player_idx, float x, float y, std::string animation);
    std::tuple<int, float, float, std::string> unpack_player(std::string message);

    std::string pack_missile_new(float x, float y);
    std::tuple<float, float> unpack_missile_new(std::string message);
}