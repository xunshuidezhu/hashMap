#ifndef HASHMAP
#define HASHMAP
#define LOG
#include <stdint.h>
#include <stdlib.h>

#ifdef __GNUC__

#if defined LOG
#define LOG cout
#endif

template <class K, class V>
struct HashNode {
public:
    K _key;
    V _val;
    HashNode* next;

public:
    HashNode(K key, V val);

    ~HashNode();

    HashNode<K, V>& operator=(const HashNode& node);
};

template <class K, class V, class Hash, class EqualKey>
class HashMap {
public:
    HashMap(int size);
    ~HashMap();
    bool insert(const K& key, const V& val);
    bool del(const K& key);
    V& find(const K& key);
    V& operator[](const K& key);

private:
    Hash hash;
    EqualKey equal;
    HashNode<K, V>** table;
    uint32_t _size;

};
#else

#endif
#endif