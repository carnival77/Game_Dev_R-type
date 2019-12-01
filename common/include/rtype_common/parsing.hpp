#pragma once
#include <vector>
#include <string>


namespace rtype_common {

    std::vector<std::string> split(std::string str, std::string delimiter);
    bool starts_with(std::string str, std::string substr);
    void print(std::vector<std::string> vec);

};
