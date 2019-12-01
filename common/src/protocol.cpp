#include "rtype_common/protocol.hpp"
#include <vector>
#include "rtype_common/parsing.hpp"


namespace rtype_common {

    std::string pack_player(int player_idx, float x, float y, std::string animation) {
        return "PLAYER:" + std::to_string(player_idx) +
                ";" + std::to_string(x) + ";" + std::to_string(y) +
                ";" + animation;
    }

    std::tuple<int, float, float, std::string> unpack_player(std::string message) {
        std::vector<std::string> split_vect = rtype_common::split(message, ":");
        split_vect = rtype_common::split(split_vect[1], ";");
        int player_idx = std::stoi(split_vect[0]);
        float x = std::stof(split_vect[1]);
        float y = std::stof(split_vect[2]);
        std::string animation = split_vect[3];
        return std::make_tuple(player_idx, x, y, animation);
    }

}