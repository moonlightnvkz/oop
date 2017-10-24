#pragma once


#include <memory>
#include "IWritableDecorator.h"

class HTMLDecorator : public IWritableDecorator {
public:
    explicit HTMLDecorator(std::shared_ptr<IWritable> writable);

    bool write(std::ostream &out) override;
};


