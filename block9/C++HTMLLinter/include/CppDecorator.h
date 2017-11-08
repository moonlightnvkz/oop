#pragma once

#include <string>
#include <unordered_set>
#include "IWritableDecorator.h"
#include "HTMLDecorator.h"

class CppDecorator : public HTMLDecorator {
public:
    explicit CppDecorator(std::shared_ptr<IWritable> writable);

    bool write(std::ostream &out) override;

protected:
    static std::unordered_set<std::string> mKeyWords;

    static constexpr const char * mColor = "0000FF";

    static std::unordered_set<std::string> mPreprocessor;

    static constexpr const char * mColorPreprocessor = "808000";
};


