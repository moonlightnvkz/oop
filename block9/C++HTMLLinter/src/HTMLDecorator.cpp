#include <sstream>
#include "../include/HTMLDecorator.h"

HTMLDecorator::HTMLDecorator(std::shared_ptr<IWritable> writable)
        : IWritableDecorator(std::move(writable)) {
}

bool HTMLDecorator::write(std::ostream &out) {
    std::stringstream ss;
    ss >> std::noskipws;
    if (!mWritable->write(ss)) {
        return false;
    }
    out << "<html>\n<body>\n<pre>\n";
    char c;
    while (ss >> c) {
        switch (c) {
            case '\'': out << "&apos;"; break;
            case '"':  out << "&quot;"; break;
            case '&':  out << "&amp;";  break;
            case '<':  out << "&lt;";   break;
            case '>':  out << "&gt;";   break;
            default:   out << c;
        }
    }
    out << "\n</pre>\n</body>\n</html>";
    return out ? true : false;
}
