//
// Created by akarpovskii on 17.09.17.
//

#pragma once


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

    Trie() = default;

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
    }

    Trie<T> &operator=(Trie &&trie) noexcept {
        if (&trie != this) {
            mRoot = std::move(mRoot);
        }
    }

    iterator begin() {
        return mRoot->begin();
    }

    const_iterator begin() const {
        return mRoot.begin();
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

    value_type &operator[](const key_type &k) {
        return mRoot[k];
    }

    std::pair<iterator, bool> insert(const key_type &k, const value_type &val) {
        mRoot->insert(k, val);
    };

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        mRoot->insert(first, last);
    }

    //удаление
    void erase(iterator position) {
        mRoot->erase(position);
    }

    size_t erase(const key_type &k) {
        mRoot->erase(k);
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
    iterator find(const key_type &k) {
        return mRoot->find(k);
    }

    const_iterator find(const key_type &k) const {
        return mRoot->find(k);
    }

    /// Returns no value if there is no such key in the Trie
    std::optional<SubTrie<T>> getSubTrie(const key_type &subKey) {
        return mRoot->getSubTrie(subKey);
    }

protected:
    std::shared_ptr<SubTrie<T>> mRoot;
};

template<class T>
class TrieIterator {
public:
    TrieIterator(const TrieIterator &mit)
            : mCurrentSubTrie(mit.mCurrentSubTrie), mRoot(mit.mRoot), mCurrentKey(mit.mCurrentKey) {
    }

    TrieIterator &operator++() {
        // If we can't go deeper
        auto currentSubTrie = mCurrentSubTrie.lock();
        if (currentSubTrie->mChildren.empty()) {
            decltype(currentSubTrie->mParent.lock()) parent;
            decltype(parent->mChildren.find(currentSubTrie->mKeyPart.value())) it;
            do {
                parent = currentSubTrie->mParent.lock();
                auto &pChildren = parent->mChildren;
                it = pChildren.find(currentSubTrie->mKeyPart.value());
                // If it is the last parent's child
                if (it == --pChildren.end()) {
                    currentSubTrie = parent;
                }
            } while (it == --parent->mChildren.begin() && currentSubTrie != mRoot.lock());
        }
        // Going deeper
        do {
            currentSubTrie = currentSubTrie->mChildren.begin()->second;
        } while(!currentSubTrie->mIsLeaf);
        mCurrentSubTrie = currentSubTrie;
        return *this;
    }

    TrieIterator operator++(int) {
        return ++TrieIterator(*this);
    }

    bool operator==(const TrieIterator &rhs) {
        return mCurrentSubTrie.lock() == rhs.mCurrentSubTrie.lock() &&
               mRoot.lock() == rhs.mRoot.lock() &&
               mCurrentKey == rhs.mCurrentKey;
    }

    bool operator!=(const TrieIterator &rhs) {
        return !(*this == rhs);
    }

    T &operator*() {
        if (!mCurrentSubTrie) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return mCurrentSubTrie->mVal;
    }

    T *operator->() {
        if (!mCurrentSubTrie) {
            throw std::out_of_range("Dereference iterator to end");
        }
        return &mCurrentSubTrie->mVal;
    }

protected:
    explicit TrieIterator(std::weak_ptr<SubTrie<T>> root, bool end = false)
            : mRoot({root}) {
        if (!end) {
            mCurrentSubTrie = root;
            decltype(mCurrentSubTrie.lock()->mChildren.begin()) it;
            while (!mCurrentSubTrie.lock()->mChildren.empty()) {
                mCurrentSubTrie = it->second;
                it = mCurrentSubTrie.lock()->mChildren.begin();
            }
        }
    }

    std::weak_ptr<SubTrie<T>> mCurrentSubTrie;

    std::weak_ptr<SubTrie<T>> mRoot;

    std::string mCurrentKey;

    friend class SubTrie<T>;
};

template<class T>
class ConstTrieIterator {
public:
    using value_type = const std::pair<std::string, T&>;

    ConstTrieIterator(const ConstTrieIterator &mit)
            : mCurrentSubTrie(mit.mCurrentSubTrie), mRoot(mit.mRoot), mCurrentVal(mit.mCurrentVal) {
    }

    ConstTrieIterator &operator++() {
        // If we can't go deeper
        auto currentSubTrie = mCurrentSubTrie.lock();
        if (currentSubTrie->mChildren.empty()) {
            decltype(currentSubTrie->mParent.lock()) parent;
            decltype(parent->mChildren.find(currentSubTrie->mKeyPart.value())) it;
            do {
                parent = currentSubTrie->mParent.lock();
                auto &pChildren = parent->mChildren;
                it = pChildren.find(currentSubTrie->mKeyPart.value());
                // If it is the last parent's child
                if (it == --pChildren.end()) {
                    currentSubTrie = parent;
                }
            } while (it == --parent->mChildren.begin() && currentSubTrie != mRoot.lock());
        }
        // Going deeper
        do {
            currentSubTrie = currentSubTrie->mChildren.begin()->second;
        } while(!currentSubTrie->mIsLeaf);
        mCurrentSubTrie = currentSubTrie;
        return *this;
    }

    ConstTrieIterator operator++(int) {
        return ++ConstTrieIterator(*this);
    }

    bool operator==(const ConstTrieIterator &rhs) {
        return false;
    }

    bool operator!=(const ConstTrieIterator &rhs) {
        return !(*this == rhs);
    }

    value_type operator*() {
        return mCurrentVal.value();
    }

    value_type *operator->() {
        return &mCurrentVal.value();
    }

protected:
    explicit ConstTrieIterator(std::weak_ptr<SubTrie<T>> root, bool end = false)
            : mRoot({root}) {
        if (!end) {
            mCurrentSubTrie = root;
            decltype(mCurrentSubTrie.lock()->mChildren.begin()) it;
            while (!mCurrentSubTrie.lock()->mChildren.empty()) {
                mCurrentSubTrie = it->second;
                it = mCurrentSubTrie.lock()->mChildren.begin();
            }
        }
    }

    /// Empty if it is the end
    std::optional<std::weak_ptr<SubTrie<T>>> mCurrentSubTrie;

    std::optional<const std::weak_ptr<SubTrie<T>>> mRoot;

    std::optional<value_type> mCurrentVal;

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

    SubTrie &operator=(const SubTrie &trie) {
        mChildren = trie.mChildren;
        mParent = trie.mParent;
        mVal = trie.mVal;
        mIsLeaf = trie.mIsLeaf;
        mKeyPart = trie.mKeyPart;
    }

    SubTrie &operator=(SubTrie &&trie) noexcept {
        mChildren = std::move(mChildren);
        mParent = std::move(trie.mParent);
        mVal = std::move(trie.mVal);
        mIsLeaf = trie.mIsLeaf;
        mKeyPart = trie.mKeyPart;
    }

    iterator begin() {
        return iterator(mParent.lock()->mChildren[mKeyPart.value()]);
    }

    const_iterator begin() const {
        return const_iterator(mParent.lock()->mChildren[mKeyPart.value()]);
    }

    iterator end() {
        return iterator(mParent.lock()->mChildren[mKeyPart.value()], true);
    }

    const_iterator end() const {
        return const_iterator(mParent.lock()->mChildren[mKeyPart.value()], true);
    }

    /// Test whether container is empty
    bool empty() const {
        return mChildren.empty();
    }

    size_t size() const {
        size_t size = 0;
        for (const auto c : mChildren) {
            size += c.second.clear();
        }
    }

    value_type &operator[](const key_type &k) {
        iterator it = find(k);
        if (it == end()) {
            return insert(k, {}).first->second;
        } else {
            return it->second;
        }
    }

    std::pair<iterator, bool> insert(const key_type &k, const value_type &val) {
        assert(!k.empty());
        if (k.size() == 1) {
            auto keyPart = k[0];
            auto it = mChildren.find(keyPart);
            auto child = mChildren[keyPart];
            child->mVal = val;
            child->mKeyPart = keyPart;
            child->mIsLeaf = true;
            return {iterator(child), (it == mChildren.end())};
        } else {
            return mChildren[k[1]]->insert(k.substr(1), val);
        }
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

    size_t erase(const key_type &k) {
        return erase(find(k));
    }

    void erase(iterator first, iterator last) {
        for (auto it = first; it < last; ++it) {
            erase(it);
        }
    }

    void swap(SubTrie &trie) {
        std::swap(mChildren, trie.mChildren);
    }

    /// очистить структуру
    void clear() {
        for (auto c : mChildren) {
            c.second.clear();
        }
        mChildren.clear();
    }

    //найти элемент
    iterator find(const key_type &k) {
        assert(!k.empty());
        if (mChildren.find(k[0]) == mChildren.end()) {
            return end();
        } else if (k.size() == 1) {
            return iterator(mChildren[k[0]]);
        } else {
            return mChildren[k[0]]->find(k.substr(1));
        }
    }

    const_iterator find(const key_type &k) const {
        assert(!k.empty());
        if (mChildren.find(k[0]) == mChildren.end()) {
            return end();
        } else if (k.size() == 1) {
            return iterator(*mChildren[k[0]]);
        } else {
            return mChildren[k[0]]->find(k.substr(1));
        }
    }

    /// Returns no value if there is no such key in the Trie
    std::optional<SubTrie<T>> getSubTrie(const key_type &subKey) {
        auto it = find(subKey);
        if (it == end()) {
            return {};
        } else {
            return std::optional{*it.mCurrentSubTrie.lock()};
        }
    }

protected:
    size_t eraseInternal(iterator position) {
        std::weak_ptr<SubTrie<T>> subTrie = position.mCurrentSubTrie.value();
        size_t count = 0;
        if (subTrie->empty()) {
            // While it is not a leaf and not the root
            while (!subTrie->mIsLeaf && subTrie->mParent.hasValue()) {
                auto tmp = subTrie;
                subTrie = subTrie->mParent.value();
                tmp.lock() = nullptr;
                ++count;
            }
        } else {
            subTrie->mIsLeaf = false;
            ++count;
        }
        return count;
    }

    friend class Trie<T>;

    friend class TrieIterator<T>;

    std::map<char, std::shared_ptr<SubTrie<T>>> mChildren;

    std::weak_ptr<SubTrie<T>> mParent;

    std::optional<value_type> mVal;

    std::optional<char> mKeyPart;

    bool mIsLeaf = false;
};