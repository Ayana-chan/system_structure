//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
#define SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H

#include <cstdint>
#include <utility>
#include <vector>

class BinarySquareMatrix {
public:
    BinarySquareMatrix() = default;

    BinarySquareMatrix(std::vector<std::vector<int>> data) : data(std::move(data)) {}

    [[nodiscard]] uint64_t get_size() const;

    /**
     * 将自己转变为可达矩阵
     * @param other
     * @return
     */
    void intoReachableMatrix();

private:
    std::vector<std::vector<int>> data;
};


#endif //SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
