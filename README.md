## c++实现的哈希映射容器

需要自定义哈希函数和键值比较函数
利用仿函数

比如
````
class Hash {
public:
    int operator()(const int& key)
    {
        int hash = 0;
        hash = hash << 7 ^ key;
        return (hash & 0x7FFFFFFF);
    }
};
````

支持插入，删除，查找以及重载[]
