#pragma once

#include <iosfwd>

class IWritable {
public:
    IWritable() = default;

    virtual ~IWritable() = default;

    virtual bool write(std::ostream &out) = 0;
};
