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
    ConstTrieIterator(const SubTrie<T> &x);

    ConstTrieIterator(const TrieIterator &mit);

    ConstTrieIterator &operator++();

    ConstTrieIterator operator++(int);

    bool operator==(const TrieIterator &rhs);

    bool operator!=(const TrieIterator &rhs);

    value_type operator*();

    value_type *operator->();
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

    SubTrie(const SubTrie<T> &trie) {
        for (auto it = trie.begin(); it != trie.end(); ++it) {
            insert(it->first, it->second);
        }
    }

    ~SubTrie() {
        clear();
    }

    SubTrie<T> &operator=(const Trie &trie) {
        clear();
        for (auto it = trie.begin(); it != trie.end(); ++it) {
            insert(it->first, it->second);
        }
    }

    iterator begin() {
        if (mChildren.empty()) {
            return end();
        }
    }

    const_iterator begin() const {
        if (mChildren.empty()) {
            return end();
        }
    }

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

    void swap(SubTrie &trie);

    void clear(); //очистить структуру

    //найти элемент
    iterator find(const key_type &k);

    const_iterator find(const key_type &k) const;

    SubTrie<T> GetSubTrie(const key_type &subKey); // получить subtree

protected:
    std::map<key_type, std::shared_ptr<SubTrie<T>>> mChildren;

    std::weak_ptr<SubTrie<T>> mParent;

    std::optional<T> mValue;    // No value if it's root

    std::string mKeyPart;
};