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

unordered_set<uint64_t> BinarySquareMatrix::calculateRs(const uint64_t &s) {
    unordered_set<uint64_t> rs;
    for (int i = 0; i < get_size(); i++) {
        if (data[s][i] == 1) {
            rs.insert(i);
        }
    }
    return rs;
}

unordered_set<uint64_t> BinarySquareMatrix::calculateAs(const uint64_t &s) {
    unordered_set<uint64_t> as;
    for (int i = 0; i < get_size(); i++) {
        if (data[i][s] == 1) {
            as.insert(i);
        }
    }
    return as;
}

unordered_set<uint64_t> BinarySquareMatrix::calculateCs_straight(const uint64_t &s) {
    unordered_set<uint64_t> cs;
    for (int i = 0; i < get_size(); i++) {
        if (data[i][s] == 1 && data[s][i] == 1) {
            cs.insert(i);
        }
    }
    return cs;
}



