#include <fstream>
#include <sstream>
#include <cmath>
#include "Cache.h"

bool FileCache::has(const std::string &key) {
    std::ifstream is(filename(key));
    return findKey(is, key) != -1;
}

std::string FileCache::read(const std::string &key) {
    std::ifstream is(filename(key));
    if (findKey(is, key)) {
        size_t length;
        if (is >> length) {   // value's length
            is.ignore(1);   //ignore '\t'
            std::string value(length, '\0');
            is.readsome(value.data(), length);
            return value;
        }
    }
    return {};
}

void FileCache::write(const std::string &key, const std::string &value) {
    std::string filename = this->filename(key);
    std::fstream fs(filename, std::ios_base::in | std::ios_base::out | std::ios_base::app);
    if (findKey(fs, key) != -1) {
        std::fpos sizeBefore = fs.tellg(); // Save current position;
        size_t length;
        fs >> length;
        fs.ignore(1).ignore(length, '\n');   // Skip '\t' before ignore the value
        std::fpos afterValue = fs.tellg();

        std::stringstream ss;
        ss << '\t' << value.length() << '\t' << value << std::endl;
        replace(fs, filename, sizeBefore, afterValue, ss.str());
    } else {
        fs.clear();
        fs << key.length() << '\t' << key << '\t' << value.length() << '\t' << value << std::endl;
    }
}

void FileCache::remove(const std::string &key) {
    std::string filename = this->filename(key);
    std::fstream fs(filename, std::ios_base::in | std::ios_base::out | std::ios_base::app);
    ssize_t keyLength = findKey(fs, key);
    if (keyLength != -1) {
        std::fpos beforeValue = fs.tellg(); // Save current position;
        ssize_t digits = static_cast<ssize_t>(std::ceil(std::log10(keyLength)));    // Determine the number of digits to rewind
        // - keyLength - '\t' - digits
        fs.seekg(- keyLength - 1 - digits, fs.cur);  // Rewind to the beginning of the line
        std::fpos before = fs.tellg(); // Save current position;

        fs.seekg(beforeValue, fs.beg);
        size_t length;
        fs >> length;
        fs.ignore(1).ignore(length, '\n');   // Skip '\t' before ignore the value
        std::fpos afterValue = fs.tellg();
        replace(fs, filename, before, afterValue, "");
    }
}

std::string FileCache::filename(const std::string &key) {
#if DEBUG
    size_t hash = key[0];
#else
    size_t hash = std::hash<std::string>()(key);
#endif
    return "./cache" + std::to_string(hash);
}

ssize_t FileCache::findKey(std::istream &is, const std::string &key) {
    ssize_t keyLength = -1;
    while (is && keyLength == -1) {
        size_t length;
        if (is >> length) {
            is.ignore(1);   //ignore '\t'
            std::string dataRead(length, '\0');
            is.read(dataRead.data(), length);
            if (dataRead == key) {
                keyLength = length;
            } else {    // Skip the value
                if (is >> length) {
                    is.ignore(1);   //ignore '\t'
                    dataRead.reserve(length);
                    is.read(dataRead.data(), length);
                }
            }
        }
    }
    return keyLength;
}

void FileCache::replace(std::fstream &fs, const std::string &filename, std::fstream::pos_type before,
                        std::fstream::pos_type after, const std::string &replacement) {
    std::fpos end = fs.seekg(0, fs.end).tellg();
    auto sizeAfter = end - after;
    std::string fileBefore(static_cast<size_t>(before), '\0');
    std::string fileAfter(static_cast<size_t>(sizeAfter), '\0');
    fs.seekg(0, fs.beg);   // Rewind
    fs.read(fileBefore.data(), before);   // Save the first part
    fs.seekg(after, fs.beg);   // Rewind
    fs.read(fileAfter.data(), sizeAfter);   // Save the second part
    fs.close();
    fs.open(filename, std::ios_base::out | std::ios_base::trunc);    // Open with trunc
    fs << fileBefore << replacement << fileAfter;
}

void PoorManMemoryCache::write(const std::string &key, const std::string &value) {
    if (mStorage.size() == mSize) {
        mStorage.erase(mStorage.begin());
    }
    if (has(key)) {
        find(key)->second = value;
    } else {
        mStorage.emplace_back(key, value);
    }
}
