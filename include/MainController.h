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

    void input_matrix();
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
