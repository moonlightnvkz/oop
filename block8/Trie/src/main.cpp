#include <iostream>
#include "../include/Trie.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Trie<int> trie;
    auto it = trie.begin();
    it = trie.end();
    ++it;
    return 0;
}