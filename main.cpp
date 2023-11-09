#include "BinaryMatrix.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    BinaryMatrix m;
    m.mulAssignWithDiffCheck(m);

    return 0;
}
