//
// Created by akarpovskii on 17.09.17.
//

#pragma once


#include <cstddef>
#include <vector>
#include <algorithm>
#include <stdexcept>

class ObjectPoolIsFull : public std::exception {
public:
    const char *what() const noexcept override {
        return "Failed to allocate an object: Object pool is full.";
    }
};

template<typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t count)
            : mCount(count), mValidity(count) {
        mMemoryPool = static_cast<T*>(operator new[] (mCount * sizeof(T)));
    }

    virtual ~ObjectPool() {
        for (size_t i = 0; i < mCount; ++i) {
            if (mValidity[i]) {
                mMemoryPool[i].~T();
            }
        }
        operator delete[] (mMemoryPool);
    }

    template<typename ...Args>
    T &alloc(Args... args) {
        if (isFull()) {
            throw ObjectPoolIsFull();
        }
        auto invalid = std::find(mValidity.begin(), mValidity.end(), false);
        auto invalidIdx = static_cast<size_t>(invalid - mValidity.begin());
        new (mMemoryPool + invalidIdx) T(std::forward<Args>(args)...);
        mValidity[invalidIdx] = true;
        return mMemoryPool[invalidIdx];
    }

    void free(T &obj) {
        if (&obj < mMemoryPool || &obj >= mMemoryPool + mCount) {
            throw std::invalid_argument("The object is not from the pool.");
        }
        obj.~T();
        mValidity.at(&obj - mMemoryPool) = false;
    }

    bool isFull() {
        return std::find(mValidity.begin(), mValidity.end(), false) == mValidity.end();
    }
protected:
    size_t mCount;

    T *mMemoryPool;

    std::vector<bool> mValidity;
};


