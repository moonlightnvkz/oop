#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "LineDecorator.h"

LineDecorator::LineDecorator(std::shared_ptr<IWritable> writable)
        : IWritableDecorator(std::move(writable)) {
}

bool LineDecorator::write(std::ostream &out) {
    std::stringstream ss;
    ss >> std::noskipws;
    if (!mWritable->write(ss)) {
        return false;
    }
    auto count = std::count(std::istreambuf_iterator<char>(ss),
                            std::istreambuf_iterator<char>(),
                            '\n');
    int digits = static_cast<int>(std::ceil(std::log10(count)));
    std::string line;
    int lineNumber = 1;
    ss.seekg(0, std::ios::beg);
    while (std::getline(ss, line)) {
        out << std::setw(digits) << lineNumber << "|\t" <<  line << std::endl;
        ++lineNumber;
    }
    return out ? true : false;
}
