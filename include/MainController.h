//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_MAINCONTROLLER_H
#define SYSTEM_STRUCTURE_MAINCONTROLLER_H

#include "BinarySquareMatrix.h"

#include <unordered_set>

class MainController {
public:
    void start();

private:
    BinarySquareMatrix matrix;

    /**
     * 输入矩阵数据，将矩阵构造到成员变量中
     */
    void inputMatrix();

    /**
     * 转为邻接矩阵
     */
    void transToReachableMatrix();

    /**
     * 计算起始集B(S)
     * @param rs_vec vector of R(Si)
     * @param bs B(S)
     */
    void calculateBeginSet(std::vector<std::unordered_set<uint64_t>> &rs_vec, std::vector<uint64_t> &bs);

    static std::vector<std::unordered_set<uint64_t>> divideRegion(std::vector<std::unordered_set<uint64_t>> &rs_vec, std::vector<uint64_t> &bs);

    static bool haveIntersection(const std::unordered_set<int>& set1, const std::unordered_set<int>& set2) {
        for (const auto& element : set1) {
            if (set2.find(element) != set2.end()) {
                return true;
            }
        }

        return false;
    }
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
