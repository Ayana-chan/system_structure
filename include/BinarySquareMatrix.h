//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
#define SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H

#include <cstdint>
#include <utility>
#include <vector>
#include <ostream>

class BinarySquareMatrix {
public:
    BinarySquareMatrix() = default;

    explicit BinarySquareMatrix(std::vector<std::vector<char>> data) : data(std::move(data)) {}

    [[nodiscard]] uint64_t get_size() const;

    /**
     * 将自己转变为可达矩阵
     * @param other
     * @return
     */
    void intoReachableMatrix();

    friend std::ostream& operator<<(std::ostream& os, const BinarySquareMatrix& matrix) {
        for (const auto& row : matrix.data) {
            for (const auto& elem : row) {
                os << static_cast<int>(elem) << ' ';
            }
            os << '\n';
        }
        return os;
    }

private:
    std::vector<std::vector<char>> data;
};


#endif //SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
