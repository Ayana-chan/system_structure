//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_BINARYMATRIX_H
#define SYSTEM_STRUCTURE_BINARYMATRIX_H

#include <vector>

class BinaryMatrix {
private:
    std::vector<std::vector<int>> data;

public:
    BinaryMatrix() = default;
    BinaryMatrix(const std::vector<std::vector<int>>& data) : data(data) {}

    /**
     * 将自己与另一个矩阵相乘，结果保存在自己这里
     * @param other
     * @return
     */
    bool mulAssignWithDiffCheck(const BinaryMatrix& other);
};


#endif //SYSTEM_STRUCTURE_BINARYMATRIX_H
