#include <iostream>
#include <map>
#include "comment.hpp"


template <typename K, typename V>
std::ostream& operator<< (std::ostream& os, std::map<K,V> const& m) {
    // structured bindings require C++17, but comment_stream doesn't per se
    for (auto const& [key, value] : m) {
        os << key << "\t:\t";
        os << value << std::endl;
    }
    return os;
}


int main () {
    std::map<std::string, double> universe;
    universe["pi"] = 3.141592;
    universe["e"] = 1.602e-19;
    universe["hbar"] = 1.055e-34;

    // wrap comment_stream around any other ostream and provide comment string
    comment_stream cs(std::cout, "# ");
    cs << universe;
    cs.toggle_commenting();
    cs << universe;
    cs.toggle_commenting();
    cs << universe;
}
