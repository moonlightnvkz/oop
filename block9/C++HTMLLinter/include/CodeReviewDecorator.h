#pragma once


#include <unordered_map>
#include "CppDecorator.h"

class CodeReviewDecorator : public CppDecorator {
public:
    explicit CodeReviewDecorator(std::shared_ptr<IWritable> writable);

    bool write(std::ostream &out) override;

protected:
    std::unordered_map<std::string, std::string> mColorMap;

    static constexpr const float mScale = 0.3f; // Empirical value
};


