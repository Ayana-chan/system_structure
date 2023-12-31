//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
#define SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H

#include <cstdint>
#include <utility>
#include <vector>
#include <ostream>
#include <unordered_set>

class BinarySquareMatrix {
public:
    std::vector<std::vector<char>> data;

    BinarySquareMatrix() = default;

    explicit BinarySquareMatrix(std::vector<std::vector<char>> data) : data(std::move(data)) {}

    [[nodiscard]] uint64_t get_size() const;

    /**
     * 将自己转变为可达矩阵
     * @param other
     * @return
     */
    void intoReachableMatrix();

    std::unordered_set<uint64_t> calculateRs(const uint64_t &s);

    std::unordered_set<uint64_t> calculateAs(const uint64_t &s);

    std::unordered_set<uint64_t> calculateCs_straight(const uint64_t &s);

    std::vector<char> &operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const BinarySquareMatrix &matrix) {
        os << "\\   ";
        for(uint64_t c = 0; c< matrix.get_size();c++){
            if (c < 10) {
                os << c << "  ";
            } else {
                os << c << " ";
            }
        }
        os << "\n";

        for(uint64_t r = 0; r< matrix.get_size();r++){
            if (r < 10) {
                os << r << "  |";
            } else {
                os << r << " |";
            }
            for (const auto &elem : matrix.data[r]) {
                os << static_cast<int>(elem) << "  ";
            }
            os << '\n';
        }
        return os;
    }
};


#endif //SYSTEM_STRUCTURE_BINARYSQUAREMATRIX_H
