#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <list>
#include <fstream>
#include <memory>
#include <utility>

class BaseCache {
public:
    virtual ~BaseCache() = default;

    virtual bool has(const std::string &key) = 0;

    virtual std::string read(const std::string &key) = 0;

    virtual void write(const std::string &key, const std::string &value) = 0;

    virtual void remove(const std::string &key) = 0;
};

class MemoryCache : public BaseCache {
public:
    bool has(const std::string &key) override {
        return mStorage.find(key) != mStorage.end();
    }

    std::string read(const std::string &key) override {
        return has(key) ? mStorage.at(key) : "";
    }

    void write(const std::string &key, const std::string &value) override {
        mStorage[key] = value;
    }

    void remove(const std::string &key) override {
        mStorage.erase(key);
    }

protected:
    std::unordered_map<std::string, std::string> mStorage;
};

class FileCache : public BaseCache {
public:
    bool has(const std::string &key) override;

    std::string read(const std::string &key) override;

    void write(const std::string &key, const std::string &value) override;

    void remove(const std::string &key) override;

protected:
    std::string filename(const std::string &key);

    /// Rewinds the stream upto required key (or the eof)
    /// @return the length of the key or -1 if key was'n found
    ssize_t findKey(std::istream &is, const std::string &key);

    /// Replaces the part (before, after) by overwriting the file
    void replace(std::fstream &fs, const std::string &filename, std::fstream::pos_type before,
                 std::fstream::pos_type after, const std::string &replacement);
};

class NullCache : public BaseCache {
public:
    bool has(const std::string &key) override {
        return false;
    }

    std::string read(const std::string &key) override {
        return {};
    }

    void write(const std::string &key, const std::string &value) override {
    }

    void remove(const std::string &key) override {
    }
};

class PoorManMemoryCache : public BaseCache {
public:
    explicit PoorManMemoryCache(size_t size = 1000)
            : mSize(size) {
    }

    bool has(const std::string &key) override {
        return find(key) != mStorage.end();
    }

    std::string read(const std::string &key) override {
        return has(key) ? find(key)->second : "";
    }

    void write(const std::string &key, const std::string &value) override;

    void remove(const std::string &key) override {
        if (has(key)) {
            mStorage.erase(find(key));
        }
    }

    size_t size() const {
        return mSize;
    }

    void size(size_t size) {
        mSize = size;
    }

protected:
    size_t mSize;

    using StorageT = std::list<std::pair<std::string, std::string>>;

    StorageT mStorage;

    StorageT::iterator find(const std::string &key) {
        return std::find_if(mStorage.begin(), mStorage.end(), [&](const auto & pair) {
            return pair.first == key;
        });
    }
};

class CacheApplier {
public:
    explicit CacheApplier(std::shared_ptr<BaseCache> strategy)
            : mStrategy(std::move(strategy)) {
    }

    virtual ~CacheApplier() = default;

    void set_strategy(std::shared_ptr<BaseCache> strategy) {
        mStrategy = std::move(strategy);
    }

    bool has_in_cache(const std::string &key) {
        return mStrategy->has(key);
    }

    std::string read_from_cache(const std::string &key) {
        return mStrategy->read(key);
    }

    void write_to_cache(const std::string &key, const std::string &value) {
        mStrategy->write(key, value);
    }

    void remove_from_cache(const std::string &key) {
        mStrategy->remove(key);
    }

protected:
    std::shared_ptr<BaseCache> mStrategy;
};


template<typename Cache>
class CacheApplierStatic {
public:
    virtual ~CacheApplierStatic() = default;

    bool has_in_cache(const std::string &key) {
        return mStrategy.has(key);
    }

    std::string read_from_cache(const std::string &key) {
        return mStrategy.read(key);
    }

    void write_to_cache(const std::string &key, const std::string &value) {
        mStrategy.write(key, value);
    }

    void remove_from_cache(const std::string &key) {
        mStrategy.remove(key);
    }

protected:
    Cache mStrategy;
};