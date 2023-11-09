//
// Created by DeathWind on 2023/11/9.
//

#include <iostream>
#include "UnionFind.h"

using namespace std;

void UnionFind::makeSet(uint64_t s) {
    //刚开始时每个bs都独立成树，归属于自己
    parent[s] = s;
    ++count;
    //秩的绝对大小没有意义，可以直接设为0
    rank[s] = 0;
}

uint64_t UnionFind::find(uint64_t i)  {
    if (parent[i] != i) {
        //查找的同时进行路径压缩
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void UnionFind::unite(uint64_t x, uint64_t y)  {
    uint64_t rootx = find(x);
    uint64_t rooty = find(y);
    if (rootx != rooty) {
        //合并到大秩的树里面去
        if (rank[rootx] < rank[rooty]) {
            swap(rootx, rooty);
        }
        parent[rooty] = rootx;
        //等秩会导致深度多一个
        if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
        --count;
    }
}

uint64_t UnionFind::getCount() const  {
    return count;
}


