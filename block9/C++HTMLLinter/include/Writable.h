#pragma once


#include <string>
#include "IWritable.h"

class Writable : public IWritable {
public:
    explicit Writable(const std::string &text);

    explicit Writable(std::string &&text);

    ~Writable() override = default;

    bool write(std::ostream &out) override;

protected:
    std::string mText;
};


