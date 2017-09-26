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

template <class T> class SubTrie;

template <class T> class TrieIterator;

template <class T> class ConstTrieIterator;


template<class T>
class Trie {
public:
    typedef TrieIterator <T> iterator;
    typedef ConstTrieIterator <T> const_iterator;

    typedef T value_type;
    typedef std::string key_type;

    Trie();

    template<class InputIterator>
    Trie(InputIterator first, InputIterator last);

    Trie(const Trie<T> &trie);

    ~Trie();

    Trie<T> &operator=(const Trie &trie);

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    bool empty() const; //Test whether container is empty

    size_t size() const;

    value_type &operator[](const key_type &k);

    std::pair<iterator, bool> insert(const key_type &k, const value_type &val);

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    //удаление
    void erase(iterator position);

    size_t erase(const key_type &k);

    void erase(iterator first, iterator last);

    void swap(Trie &trie);

    void clear(); //очистить структуру

    //найти элемент
    iterator find(const key_type &k);

    const_iterator find(const key_type &k) const;

    SubTrie<T> GetSubTrie(const key_type &subKey); // получить subtree

protected:
    std::shared_ptr<SubTrie<T>> mRoot;
};

template<class T>
class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T &>> {
public:
    TrieIterator(const SubTrie<T> &x);

    TrieIterator(const TrieIterator &mit);

    TrieIterator &operator++();

    TrieIterator operator++(int);

    bool operator==(const TrieIterator &rhs);

    bool operator!=(const TrieIterator &rhs);

    value_type operator*();

    value_type *operator->();
};

template<class T>
class ConstTrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T &>> {
public:
    explicit ConstTrieIterator(const SubTrie<T> &x)
            : mCurrent({&x}) {
    }

    ConstTrieIterator(const TrieIterator &mit) = default;

    ConstTrieIterator &operator++() {
        if (mCurrent) {

        }
        return *this;
    }

    ConstTrieIterator operator++(int);

    bool operator==(const TrieIterator &rhs);

    bool operator!=(const TrieIterator &rhs);

    value_type operator*();

    value_type *operator->();

protected:
    ConstTrieIterator() = default;

    std::optional<SubTrie<T>*> mCurrent;
};

template <class T>
class SubTrie {
    typedef TrieIterator <T> iterator;
    typedef ConstTrieIterator <T> const_iterator;

    typedef T value_type;
    typedef std::string key_type;

    SubTrie() = default;

    template<class InputIterator>
    SubTrie(InputIterator first, InputIterator last) {
        for (auto it = first; it != last; ++it) {
            insert(it->first, it->second);
        }
    }

    SubTrie(const SubTrie<T> &trie) = default;

    ~SubTrie() {
        clear();
    }

    SubTrie<T> &operator=(const Trie &trie) = default;

    iterator begin() {
        const SubTrie<T> *st = this;
        if (mChildren.empty()) {
            return end();
        }
        while (!st->mChildren.empty()) {
            st = *st->mChildren.begin();
        }
        return iterator(*st);
    }

    const_iterator begin() const {
        const SubTrie<T> *st = this;
        if (mChildren.empty()) {
            return end();
        }
        while (!st->mChildren.empty()) {
            st = *st->mChildren.begin();
        }
        return const_iterator(*st);
    }

    iterator end() {
        const SubTrie<T> *st = this;
        if (mChildren.empty()) {
            return end();
        }
        while (!st->mChildren.empty()) {
            st = *st->mChildren.rbegin();
        }
        return iterator(*st);
    }

    const_iterator end() const {
        const SubTrie<T> *st = this;
        if (mChildren.empty()) {
            return end();
        }
        while (!st->mChildren.empty()) {
            st = *st->mChildren.rbegin();
        }
        return const_iterator(*st);
    }

    bool empty() const; //Test whether container is empty

    size_t size() const;

    value_type &operator[](const key_type &k);

    std::pair<iterator, bool> insert(const key_type &k, const value_type &val);

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    //удаление
    void erase(iterator position);

    size_t erase(const key_type &k);

    void erase(iterator first, iterator last);

    void swap(SubTrie &trie);

    void clear(); //очистить структуру

    //найти элемент
    iterator find(const key_type &k);

    const_iterator find(const key_type &k) const;

    SubTrie<T> GetSubTrie(const key_type &subKey); // получить subtree

protected:
    std::map<key_type, std::shared_ptr<SubTrie<T>>> mChildren;

    std::weak_ptr<SubTrie<T>> mParent;

    std::optional<T> mValue;    // No value if it's root or end

    std::string mKeyPart;
};