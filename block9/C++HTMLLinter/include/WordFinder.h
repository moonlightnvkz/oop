#pragma once


#include <istream>

class WordFinder {
public:
    explicit WordFinder(std::istream &is);

    virtual ~WordFinder() = default;

    std::pair<std::string, bool> next(bool &end);
protected:
    std::istream &mInput;
};


