//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_MAINCONTROLLER_H
#define SYSTEM_STRUCTURE_MAINCONTROLLER_H

#include "BinarySquareMatrix.h"

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
     * @return B(S)
     */
    std::vector<uint64_t> calculateBeginSet();
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
