#include <iostream>
#include "ArgumentsParser.h"

int main(int argc, char *argv[]) {
    ArgumentsParser argumentsParser({"--calc", "--check"});

    const std::vector<std::pair<Key, Values>> args = argumentsParser.parse(argc, argv);


    return 0;
}