#include <sstream>
#include "../include/WordFinder.h"

WordFinder::WordFinder(std::istream &is)
        : mInput(is) {
}

std::pair<std::string, bool> WordFinder::next(bool &end) {
    end = false;
    std::stringstream ss;
    mInput >> std::noskipws;
    char c;
    bool wordIsEmpty = true;
    bool needToContinue = true;
    bool isWord = false;
    while (c = static_cast<char>(mInput.peek()), mInput && c != std::char_traits<char>::eof() && needToContinue) {
        switch (c) {
            case '0'...'9':
                if (wordIsEmpty) {
                    isWord = false;
                    wordIsEmpty = false;
                }
                [[fallthrough]]
            case '#':       [[fallthrough]]
            case '_':       [[fallthrough]]
            case 'a'...'z': [[fallthrough]]
            case 'A'...'Z':
                if (wordIsEmpty) {
                    isWord = true;
                    wordIsEmpty = false;
                }
                mInput >> c;
                ss << c;
                break;
            default:
                if (!wordIsEmpty && isWord) {
                    needToContinue = false;
                } else {
                    if (std::string(" \t\n,;.()[]{}:\'\"").find(c) != std::string::npos) {
                        needToContinue = false;
                    } else {
                        isWord = false;
                        wordIsEmpty = false;
                    }
                    mInput >> c;
                    ss << c;
                }
        }
    }

    if (c == std::char_traits<char>::eof()) {
        mInput >> c;    // set eof flag
    }
    if (!mInput) {
        end = true;
    }
    return {ss.str(), isWord};
}
