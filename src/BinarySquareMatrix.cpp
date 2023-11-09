//
// Created by DeathWind on 2023/11/9.
//

#include "BinarySquareMatrix.h"

#include <iostream>

using namespace std;

uint64_t BinarySquareMatrix::get_size() const {
    return data.size();
}

void BinarySquareMatrix::intoReachableMatrix() {
//    cout << "intoReachableMatrix" << endl;
    auto m_size = get_size();

    //直接用Floyd算法
    for (size_t k = 0; k < m_size; ++k) {
        for (size_t r = 0; r < m_size; ++r) {
            auto r_to_k = data[r][k]; //for cache friendly
            for (size_t c = 0; c < m_size; ++c) {
                data[r][c] = data[r][c] || r == c || (r_to_k && data[k][c]);
            }
        }
    }
}


