#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Writable.h"
#include "../include/HTMLDecorator.h"
#include "../include/LineDecorator.h"
#include "../include/WordFinder.h"
#include "../include/CppDecorator.h"
#include "../include/CodeReviewDecorator.h"

int main() {
    std::ifstream is("src/main.cpp");
    std::stringstream ss;
    std::copy(std::istreambuf_iterator<char>(is),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(ss));
    std::ofstream os("main.html");
    std::shared_ptr<IWritable> writable = std::make_shared<Writable>(ss.str());
    CodeReviewDecorator decorator(writable);
    decorator.write(os);
//    std::stringstream ss;
//    ss.str("#include word1.word2 1word->2word std::namespace");
//    bool end = false;
//    WordFinder finder(ss);
//    while (!end) {
//        auto res = finder.next(end);
//        std::cout << res.first << " " << std::boolalpha << res.second << std::endl;
//    }
    return 0;
}