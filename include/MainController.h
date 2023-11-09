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
    void input_matrix();

    /**
     * 转为邻接矩阵
     */
    void trans_to_reachable_matrix();
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
