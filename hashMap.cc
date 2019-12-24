#include "hashMap.h"
#include <bits/stdc++.h>

using namespace std;

template <class K, class V>
HashNode<K, V>::HashNode(K key, V val)
{
    _key = key;
    _val = val;
    next = 0;
}

template <class K, class V>
HashNode<K, V>::~HashNode()
{
    LOG << "~HashNode" << endl;
}

template <class K, class V>
inline HashNode<K, V>& HashNode<K, V>::operator=(const HashNode<K, V>& node)
{
    _key = node._key;
    _val = node._val;
    next = node.next;
    return *this;
}

template <class K, class V, class Hash, class EqualKey>
HashMap<K, V, Hash, EqualKey>::HashMap(int size)
    : _size(size)
    , hash()
    , equal()
{
    table = new HashNode<K, V>*[_size];
    for (uint32_t i = 0; i < _size; i++) {
        table[i] = NULL;
    }
}

template <class K, class V, class Hash, class EqualKey>
HashMap<K, V, Hash, EqualKey>::~HashMap()
{
    for (uint32_t i = 0; i < _size; i++) {
        HashNode<K, V>* currentNode = table[i];
        while (currentNode != 0) {
            HashNode<K, V>* tmp = currentNode;
            currentNode = currentNode->next;
            delete tmp;
        }
    }
    delete table;
}

template <class K, class V, class Hash, class EqualKey>
bool HashMap<K, V, Hash, EqualKey>::insert(const K& key, const V& val)
{
    int index = hash(key) % _size;
    HashNode<K, V>* node = new HashNode<K, V>(key, val);
    node->next = table[index];
    table[index] = node;
    return true;
}

template <class K, class V, class Hash, class EqualKey>
bool HashMap<K, V, Hash, EqualKey>::del(const K& key)
{
    uint32_t index = hash(key) % _size;
    HashNode<K, V>* node = table[index];
    HashNode<K, V>* prev = NULL;
    while (node) {
        if (node->_key == key) {
            if (prev == NULL) {
                table[index] = node->next;
            } else {
                prev->next = node->next;
            }
            delete node;
            return true;
        }
        prev = node;
        node = node->next;
    }
}

template <class K, class V, class Hash, class EqualKey>
V& HashMap<K, V, Hash, EqualKey>::find(const K& key)
{
    uint32_t index = hash(key) % _size;
    V fail = 0;
    if (table[index] == 0) {
        return fail;
    } else {
        HashNode<K, V>* node = table[index];
        while (node) {
            if (node->_key == key) {
                return node->_val;
            }
            node = node->next;
        }
    }
}

template <class K, class V, class Hash, class EqualKey>
V& HashMap<K, V, Hash, EqualKey>::operator[](const K& key)
{
    return find(key);
}

//hash函数
class Hash {
public:
    int operator()(const int& key)
    {
        int hash = 0;
        hash = hash << 7 ^ key;
        return (hash & 0x7FFFFFFF);
    }
};

class EqualKey {
public:
    bool operator()(const int& left, const int& right)
    {
        if (left < right) {
            return false;
        } else {
            return true;
        }
    }
};

int main()
{
    HashNode<int, int> node(1, 2);
    HashMap<int, int, Hash, EqualKey> map(10);
    map.insert(0, 2);
    //LOG << map.del(0) << endl;
    LOG << map.find(0) << endl;
    LOG << map[0] << endl;
    if (map.del(0)) {
        LOG << "del correct" << endl;
    }
}