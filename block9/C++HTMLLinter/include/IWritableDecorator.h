#pragma once

#include <memory>
#include "IWritable.h"

class IWritableDecorator : public IWritable {
public:
    explicit IWritableDecorator(std::shared_ptr<IWritable> writable)
            : mWritable(std::move(writable)) {
    }

    bool write(std::ostream &out) override = 0;

protected:
    std::shared_ptr<IWritable> mWritable;
};
