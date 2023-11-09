//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_UNIONFIND_H
#define SYSTEM_STRUCTURE_UNIONFIND_H

#include <vector>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>

/**
 * 并查集，适配unordered_set<uint64_t>
 */
class UnionFind {
public:
    void makeSet(uint64_t s);

    /**
     * 查找父的同时进行路径压缩
     * @param i
     * @return
     */
    uint64_t find(uint64_t i);

    /**
     * 合并集合，并尽量减少秩
     * @param x
     * @param y
     */
    void unite(uint64_t x, uint64_t y);

    [[nodiscard]] uint64_t getCount() const;

private:
    std::unordered_map<uint64_t , uint64_t> parent;
    std::unordered_map<uint64_t, int> rank;
    int count;
};


#endif //SYSTEM_STRUCTURE_UNIONFIND_H
