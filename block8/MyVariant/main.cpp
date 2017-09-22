#include <iostream>
#include <string>
#include <cassert>
#include "include/variant.hpp"

struct Test {
    Test() = default;

    explicit Test(int i) {
        std::cout << i << std::endl;
    }

    explicit operator float() const {
        return 1.1f;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    my_variant::variant<int, char> myVariant = 1;
    static_assert(my_variant::details::is_streamable<int>::value);
    assert(myVariant.can_convert<std::string>());
    std::cout << myVariant.convert<std::string>() << std::endl;
    return 0;
}