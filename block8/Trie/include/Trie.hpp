//
// Created by akarpovskii on 17.09.17.
//

#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <map>
#include <utility>
#include <cassert>

template <class T> class SubTrie;

template <class T> class TrieIterator;

template <class T> class ConstTrieIterator;

template<class T>
class Trie {
public:
    typedef TrieIterator <T> iterator;
    typedef ConstTrieIterator <T> const_iterator;

    typedef T value_type;
    typedef std::string_view key_type;

    Trie() {
        mRoot.reset(new SubTrie<T>(*this));
    }

    template<class InputIterator>
    Trie(InputIterator first, InputIterator last) {
        insert(first, last);
    }

    Trie(const Trie &trie)
            : mRoot(trie.mRoot) {
    }

    Trie(Trie &&trie) noexcept
            : mRoot(std::move(mRoot)){
    }

    virtual ~Trie() = default;

    Trie<T> &operator=(const Trie &trie) {
        if (&trie != this) {
            mRoot = trie.mRoot;
        }
        return *this;
    }

    Trie<T> &operator=(Trie &&trie) noexcept {
        if (&trie != this) {
            mRoot = std::move(mRoot);
        }
        return *this;
    }

    iterator begin() {
        return mRoot->begin();
    }

    const_iterator begin() const {
        return static_cast<const SubTrie<T> *>(mRoot.get())->begin();
    }

    iterator end() {
        return mRoot->end();
    }

    const_iterator end() const {
        return mRoot->end();
    }

    /// Test whether container is empty
    bool empty() const {
        return mRoot->empty();
    }

    size_t size() const {
        return mRoot->size();
    }

    value_type &operator[](key_type k) {
        return mRoot->operator[](k);
    }

    std::pair<iterator, bool> insert(key_type k, const value_type &val) {
        return mRoot->insert(k, val);
    };

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        mRoot->insert(first, last);
    }

    //удаление
    void erase(iterator position) {
        mRoot->erase(position);
    }

    size_t erase(key_type k) {
        return mRoot->erase(k);
    }

    void erase(iterator first, iterator last) {
        mRoot->erase(first, last);
    }

    void swap(Trie &trie) {
        std::swap(mRoot, trie.mRoot);
    }

    /// очистить структуру
    void clear() {
        mRoot->clear();
    }

    /// найти элемент
    iterator find(key_type k) {
        return mRoot->find(k);
    }

    const_iterator find(key_type k) const {
        return mRoot->find(k);
    }

    /// Returns no value if there is no such key in the Trie
    std::optional<SubTrie<T>> getSubTrie(key_type subKey) {
        return mRoot->getSubTrie(subKey);
    }

protected:
    std::shared_ptr<SubTrie<T>> mRoot;

    friend class SubTrie<T>;
};

template<class T>
class TrieIterator {
public:
    TrieIterator(const TrieIterator &mit)
            : mRoot(mit.mRoot), mCurrentSubTrie(mit.mCurrentSubTrie), mCurrentKey(mit.mCurrentKey) {
    }

    virtual ~TrieIterator() = default;

    TrieIterator &operator++() {
        auto currentShared = mCurrentSubTrie.lock();
        if (currentShared->mChildren.empty()) { // If we can't go deeper
            auto rootShared = mRoot.lock();
            for (;;) {
                bool isRoot = currentShared == rootShared;
                // If we have reached the root,
                // it has no other children except we iterated through.
                // Return an iterator to the end.
                if (isRoot) {
                    mCurrentSubTrie.reset();
                    mCurrentKey.clear();
                    return *this;
                }
                auto parent = currentShared->mParent.lock();
                auto currentIter = parent->mChildren.find(currentShared->mKeyPart);
                bool isLastChild = currentIter == --parent->mChildren.end();
                if (!isLastChild) {
                    // The root's mKeyPart is not taken into account.
                    // So the mCurrentKey might be empty if the parent is the root.
                    // pop_back on empty string cause UB.
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                    currentShared = (++currentIter)->second;
                    mCurrentKey += currentShared->mKeyPart;
                    break;
                } else {
                    currentShared = parent;
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                }
            }
        }
        // If we have reached this, we already changed the branch.
        // Just go deeper.
        while(!currentShared->mChildren.empty()) {
            currentShared = currentShared->mChildren.begin()->second;
            mCurrentKey += currentShared->mKeyPart;
        }
        mCurrentSubTrie = currentShared;
        return *this;
    }

    TrieIterator operator++(int) {
        auto that = *this;
        ++*this;
        return that;
    }

    bool operator==(const TrieIterator &rhs) const {
        return mCurrentSubTrie.lock() == rhs.mCurrentSubTrie.lock() &&
               mRoot.lock() == rhs.mRoot.lock() &&
               mCurrentKey == rhs.mCurrentKey;
    }

    bool operator!=(const TrieIterator &rhs) const {
        return !(*this == rhs);
    }

    T &operator*() const {
        auto shared = mCurrentSubTrie.lock();
        if (!shared) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return shared->mVal.value();
    }

    T *operator->() const {
        auto shared = mCurrentSubTrie.lock();
        if (!shared) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return &shared->mVal.value();
    }

    const std::string &key() const {
        return mCurrentKey;
    }

protected:
    explicit TrieIterator(std::weak_ptr<SubTrie<T>> root, bool end = false)
            : mRoot(root) {
        if (!end) {
            decltype(mCurrentSubTrie.lock()->mChildren.begin()) it;
            auto currentShared = mRoot.lock();
            while (currentShared && !currentShared->mChildren.empty()) {
                currentShared = currentShared->mChildren.begin()->second;
                mCurrentKey += currentShared->mKeyPart;
            }
            if (currentShared != mRoot.lock()) {
                mCurrentSubTrie = currentShared;
            }
        }
    }

    explicit TrieIterator(std::weak_ptr<SubTrie<T>> root, std::weak_ptr<SubTrie<T>> current)
            : mRoot(root), mCurrentSubTrie(current) {
        auto currentSubTrie = current.lock();
        auto rootShared = root.lock();
        while (currentSubTrie != rootShared && currentSubTrie->mParent.lock()) {
            mCurrentKey += currentSubTrie->mKeyPart;
            currentSubTrie = currentSubTrie->mParent.lock();
        }
        std::reverse(mCurrentKey.begin(), mCurrentKey.end());
    }

    std::weak_ptr<SubTrie<T>> mRoot;

    std::weak_ptr<SubTrie<T>> mCurrentSubTrie;

    std::string mCurrentKey;

    friend class SubTrie<T>;
};

template<class T>
class ConstTrieIterator {
public:
    ConstTrieIterator(const ConstTrieIterator &mit)
            : mRoot(mit.mRoot), mCurrentSubTrie(mit.mCurrentSubTrie), mCurrentKey(mit.mCurrentKey) {
    }

    virtual ~ConstTrieIterator() = default;

    ConstTrieIterator &operator++() {
        auto currentShared = mCurrentSubTrie.lock();
        if (currentShared->mChildren.empty()) { // If we can't go deeper
            auto rootShared = mRoot.lock();
            for (;;) {
                bool isRoot = currentShared == rootShared;
                // If we have reached the root,
                // it has no other children except we iterated through.
                // Return an iterator to the end.
                if (isRoot) {
                    mCurrentSubTrie.reset();
                    mCurrentKey.clear();
                    return *this;
                }
                auto parent = currentShared->mParent.lock();
                auto currentIter = parent->mChildren.find(currentShared->mKeyPart);
                bool isLastChild = currentIter == --parent->mChildren.end();
                if (!isLastChild) {
                    // The root's mKeyPart is not taken into account.
                    // So the mCurrentKey might be empty if the parent is the root.
                    // pop_back on empty string cause UB.
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                    currentShared = (++currentIter)->second;
                    mCurrentKey += currentShared->mKeyPart;
                    break;
                } else {
                    currentShared = parent;
                    if (!mCurrentKey.empty()) {
                        mCurrentKey.pop_back();
                    }
                }
            }
        }
        // If we have reached this, we already changed the branch.
        // Just go deeper.
        while(!currentShared->mChildren.empty()) {
            currentShared = currentShared->mChildren.begin()->second;
            mCurrentKey += currentShared->mKeyPart;
        }
        mCurrentSubTrie = currentShared;
        return *this;
    }

    ConstTrieIterator operator++(int) {
        auto that = *this;
        ++*this;
        return that;
    }

    bool operator==(const ConstTrieIterator &rhs) const {
        return mCurrentSubTrie.lock() == rhs.mCurrentSubTrie.lock() &&
               mRoot.lock() == rhs.mRoot.lock() &&
               mCurrentKey == rhs.mCurrentKey;
    }

    bool operator!=(const ConstTrieIterator &rhs) const {
        return !(*this == rhs);
    }

    T &operator*() const {
        auto shared = mCurrentSubTrie.lock();
        if (!shared) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return shared->mVal.value();
    }

    T *operator->() const {
        auto shared = mCurrentSubTrie.lock();
        if (!shared) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return &shared->mVal.value();
    }

    const std::string &key() const {
        return mCurrentKey;
    }

protected:
    explicit ConstTrieIterator(std::weak_ptr<SubTrie<T>> root, bool end = false)
            : mRoot(root) {
            if (!end) {
                decltype(mCurrentSubTrie.lock()->mChildren.begin()) it;
                auto currentShared = mRoot.lock();
                while (currentShared && !currentShared->mChildren.empty()) {
                    currentShared = currentShared->mChildren.begin()->second;
                    mCurrentKey += currentShared->mKeyPart;
                }
                if (currentShared != mRoot.lock()) {
                    mCurrentSubTrie = currentShared;
                }
            }
    }

    explicit ConstTrieIterator(std::weak_ptr<SubTrie<T>> root, std::weak_ptr<SubTrie<T>> current)
            : mRoot(root), mCurrentSubTrie(current) {
        auto currentSubTrie = current.lock();
        auto rootShared = root.lock();
        while (currentSubTrie != rootShared && currentSubTrie->mParent.lock()) {
            mCurrentKey += currentSubTrie->mKeyPart;
            currentSubTrie = currentSubTrie->mParent.lock();
        }
        std::reverse(mCurrentKey.begin(), mCurrentKey.end());
    }

    std::weak_ptr<SubTrie<T>> mRoot;

    std::weak_ptr<SubTrie<T>> mCurrentSubTrie;

    std::string mCurrentKey;

    friend class SubTrie<T>;
};

template <class T>
class SubTrie {
public:
    typedef TrieIterator <T> iterator;
    typedef ConstTrieIterator <T> const_iterator;

    typedef T value_type;
    typedef std::string_view key_type;

    SubTrie() = default;

    template<class InputIterator>
    SubTrie(InputIterator first, InputIterator last) {
        insert(first, last);
    }

    SubTrie(const SubTrie &trie) {
        *this = trie;
    }

    SubTrie(SubTrie &&trie) noexcept {
        *this = std::move(trie);
    }

    virtual ~SubTrie() = default;

    SubTrie &operator=(const SubTrie &that) {
        if (this != &that) {
            mChildren = that.mChildren;
            mParent = that.mParent;
            mVal = that.mVal;
            mIsLeaf = that.mIsLeaf;
            mKeyPart = that.mKeyPart;
        }
        return *this;
    }

    SubTrie &operator=(SubTrie &&that) noexcept {
        if (this != &that) {
            mChildren = std::move(mChildren);
            mParent = std::move(that.mParent);
            mVal = std::move(that.mVal);
            mIsLeaf = that.mIsLeaf;
            mKeyPart = that.mKeyPart;
        }
        return *this;
    }

    iterator begin() {
        return iterator(thisShared());
    }

    const_iterator begin() const {
        return const_iterator(thisShared());
    }

    iterator end() {
        return iterator(thisShared(), true);
    }

    const_iterator end() const {
        return const_iterator(thisShared(), true);
    }

    /// Test whether container is empty
    bool empty() const {
        return mChildren.empty();
    }

    size_t size() const {
        size_t size = mIsLeaf ? 1 : 0;
        for (const auto c : mChildren) {
            if (c.second) {
                size += c.second->size();
            }
        }
        return size;
    }

    value_type &operator[](key_type k) {
        iterator it = find(k);
        if (it == end()) {
            return *insert(k, {}).first;
        } else {
            return *it;
        }
    }

    std::pair<iterator, bool> insert(key_type k, const value_type &val) {
        assert(!k.empty());
        size_t size = k.size();
        size_t sizem1 = size - 1;
        std::shared_ptr<SubTrie<T>> current = thisShared(), prev;
        bool created = false;
        for (size_t i = 0; i < size; ++i) {
            char keyPart = k[i];
            prev = current;
            auto &child = current->mChildren[keyPart];
            if (!child) {
                child.reset(new SubTrie<T>());
            }
            if (!child->mIsLeaf) {
                child->mParent = prev;
                child->mKeyPart = keyPart;
                created = true;
            }
            if (i == sizem1) {
                child->mVal = val;
                child->mIsLeaf = true;
            }
            current = child;
        }
        return {iterator(thisShared(), current), created};
    };

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for (auto it = first; it != last; ++it) {
            insert(it->first, it->second);
        }
    }

    //удаление
    void erase(iterator position) {
        eraseInternal(position);
    }

    size_t erase(key_type k) {
        auto f = find(k);
        return eraseInternal(f);
    }

    void erase(iterator first, iterator last) {
        for (auto it = first; it != last; ) {
            erase(it++);
        }
    }

    void swap(SubTrie &trie) {
        std::swap(mChildren, trie.mChildren);
    }

    /// очистить структуру
    void clear() {
        for (auto c : mChildren) {
            c.second->clear();
        }
        mChildren.clear();
    }

    //найти элемент
    iterator find(key_type k) {
        assert(!k.empty());
        size_t size = k.size();
        std::shared_ptr<SubTrie<T>> current = thisShared();
        for (size_t i = 0; i < size; ++i) {
            auto it = current->mChildren.find(k[i]);
            if (it == current->mChildren.end()) {
                return end();
            }
            current = it->second;
        }
        return current->mIsLeaf ? iterator(thisShared(), current) : end();
    }

    const_iterator find(key_type k) const {
        assert(!k.empty());
        size_t size = k.size();
        std::shared_ptr<SubTrie<T>> current = thisShared();
        for (size_t i = 0; i < size; ++i) {
            auto it = current->mChildren.find(k[i]);
            if (it == current->mChildren.end()) {
                return end();
            }
            current = it->second;
        }
        return current->mIsLeaf ? const_iterator(thisShared(), current) : end();
    }

    /// Returns no value if there is no such key in the Trie
    std::optional<SubTrie<T>> getSubTrie(key_type subKey) {
        auto it = find(subKey);
        if (it == end()) {
            return {};
        } else {
            return std::optional{*it.mCurrentSubTrie.lock()};
        }
    }

    value_type &getRootValue() {
        assert(mVal.has_value());
        return mVal.value();
    }

protected:
    /// Only for root creation.
    /// Should not be used somewhere else.
    explicit SubTrie(const Trie<T> &trie)
            : mTrie(&trie) {
    }

    std::shared_ptr<SubTrie<T>> thisShared() const {
        auto parentShared = mParent.lock();
        return parentShared ?
               parentShared->mChildren.find(mKeyPart)->second :
               mTrie->mRoot;
    }
    size_t eraseInternal(iterator position) {
        if (position == end()) {
            return 0;
        }
        std::shared_ptr<SubTrie<T>> subTrie = position.mCurrentSubTrie.lock();
        size_t count = 0;
        subTrie->mIsLeaf = false;
        if (subTrie->mChildren.empty()) {
            // Go up while it is neither a leaf nor the root
            for (auto parentShared = subTrie->mParent.lock();
                 parentShared && !subTrie->mIsLeaf && subTrie->mChildren.empty();
                 parentShared = subTrie->mParent.lock())
            {
                parentShared->mChildren.erase(subTrie->mKeyPart);
                subTrie = parentShared;
                ++count;
            }
        } else {
            count = 1;
        }
        return count;
    }

    friend class Trie<T>;

    friend class TrieIterator<T>;

    friend class ConstTrieIterator<T>;

    /// Only for usage in the root node.
    /// Is used only for creation first level nodes
    /// due to the need of the weak_ptr to the parent.
    const Trie<T> *mTrie = nullptr;

    std::map<char, std::shared_ptr<SubTrie<T>>> mChildren;

    std::weak_ptr<SubTrie<T>> mParent;

    /// Only root has no value
    std::optional<value_type> mVal;

    char mKeyPart = char(0);

    bool mIsLeaf = false;
};