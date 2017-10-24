#pragma once


#include <memory>
#include "IWritableDecorator.h"

class LineDecorator : public IWritableDecorator {
public:
    explicit LineDecorator(std::shared_ptr<IWritable> writable);

    bool write(std::ostream &out) override;
};