//
// Created by DeathWind on 2023/11/9.
//

#include "MainController.h"

#include <iostream>

using namespace std;

void MainController::start() {
    input_matrix();
    trans_to_reachable_matrix();
}

void MainController::input_matrix() {
    cout << "Input Matrix.\n";
    cout << "Example: node_num edge_num from1 to1 from2 to2\n";
    cout << "Notice: index start with 0\n";

    uint64_t nodeNum;
    cin >> nodeNum;
    auto data(vector<vector<char>>(nodeNum, vector<char>(nodeNum, 0)));

    uint64_t edge_num;
    cin >> edge_num;
    uint64_t from, to;
    for (int _i = 0; _i < edge_num; _i++) {
        cin >> from;
        cin >> to;
//        cout << "DEBUG: from " << from << " to " << to << "\n";
        data[from][to] = 1;
    }

    matrix = BinarySquareMatrix(data);

    //打印矩阵
    cout << "Get Matrix: \n";
    cout<< matrix;
    cout << "\n";
}

void MainController::trans_to_reachable_matrix() {
    matrix.intoReachableMatrix();

    //打印邻接矩阵
    cout << "Reachable Matrix: \n";
    cout<< matrix;
    cout << "\n";
}
