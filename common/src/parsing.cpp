#include "rtype_common/parsing.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>


std::vector<std::string> rtype_common::split(std::string str, std::string delimiter) {
    std::vector<std::string> split_vect;
    boost::split(split_vect, str, boost::is_any_of(delimiter));
    return split_vect;
}


bool rtype_common::starts_with(std::string str, std::string substr) {
    return boost::starts_with(str, substr);
}


void rtype_common::print(std::vector<std::string> vec) {
    for (auto e = vec.begin(); e != vec.end(); e++) {
        std::cout << *e << " ";
    }
    std::cout << "\n";
}
