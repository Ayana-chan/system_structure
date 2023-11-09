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
    std::vector<std::unordered_set<uint64_t>> rs_vec, cs_vec;
    std::vector<uint64_t> bs;

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
    void calculateBeginSet();

    /**
     * 划分区域
     * @param rs_vec
     * @param bs
     * @return
     */
    std::vector<std::unordered_set<uint64_t>> divideParts();

    void divideLevel(std::vector<std::unordered_set<uint64_t>> &levels, const std::unordered_set<uint64_t> &part);
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
