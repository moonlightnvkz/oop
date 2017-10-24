#include <sstream>
#include <random>
#include "CodeReviewDecorator.h"
#include "WordFinder.h"

CodeReviewDecorator::CodeReviewDecorator(std::shared_ptr<IWritable> writable)
        : CppDecorator(std::move(writable)) {
}

bool CodeReviewDecorator::write(std::ostream &out) {
    static std::mt19937 generator;
    static std::uniform_int_distribution<uint16_t> distribution;
    std::stringstream ss;
    // Color key words manually
    if (!HTMLDecorator::write(ss)) {
        return false;
    }
    WordFinder finder(ss);
    bool end = false;
    while (!end) {
        auto res = finder.next(end);
        if (res.second) {
            if (mKeyWords.find(res.first) != mKeyWords.end()) {
                out << "<font color=" << mColor << ">" << res.first << "</font>";
                continue;
            } else if (mColorMap.find(res.first) == mColorMap.end()) {
                auto R = static_cast<uint16_t>(distribution(generator) * mScale);
                auto G = static_cast<uint16_t>(distribution(generator) * mScale);
                auto B = static_cast<uint16_t>(distribution(generator) * mScale);
                std::stringstream color;
                color << std::hex << R << G << B;
                mColorMap[res.first] = color.str();
            }
            out << "<font color=" << mColorMap[res.first] << ">" << res.first << "</font>";
        } else {
            out << res.first;
        }
    }
    return out ? true : false;
}
