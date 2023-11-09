//
// Created by DeathWind on 2023/11/9.
//

#include "MainController.h"
#include "UnionFind.h"

#include <iostream>
#include <algorithm>

using namespace std;

void MainController::start() {
    inputMatrix();
    transToReachableMatrix();
    cout << "1. Divide Parts\n";
    vector<unordered_set<uint64_t>> rs_vec;
    vector<uint64_t> bs;
    calculateBeginSet(rs_vec, bs);
    divideParts(rs_vec, bs);
}

void MainController::inputMatrix() {
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
    cout << matrix;
    cout << "\n";
}

void MainController::transToReachableMatrix() {
    matrix.intoReachableMatrix();

    //打印邻接矩阵
    cout << "Reachable Matrix: \n";
    cout << matrix;
    cout << "\n";
}

void MainController::calculateBeginSet(vector<unordered_set<uint64_t>> &rs_vec, vector<uint64_t> &bs) {
    rs_vec.resize(matrix.get_size());
    bs.clear();

    cout << "--------\n";
    for (uint64_t s = 0; s < matrix.get_size(); s++) {
        auto &rs = rs_vec[s];
        for (int i = 0; i < matrix.get_size(); i++) {
            if (matrix[s][i] == 1) {
                rs.insert(i);
            }
        }
        cout << "R(" << s << "): ";
        for (auto &elem: rs) {
            cout << elem << " ";
        }
        cout << "\n";

        unordered_set<uint64_t> as;
        for (int i = 0; i < matrix.get_size(); i++) {
            if (matrix[i][s] == 1) {
                as.insert(i);
            }
        }
        cout << "A(" << s << "): ";
        for (auto &elem: as) {
            cout << elem << " ";
        }
        cout << "\n";

        unordered_set<uint64_t> cs;
        // 取rs和as的交集
        for (auto &elem: as) {
            if (rs.count(elem) != 0) {
                cs.insert(elem);
            }
        }
        cout << "C(" << s << "): ";
        for (auto &elem: cs) {
            cout << elem << " ";
        }
        cout << "\n";

        // 判断是否为Bs
        if (as == cs) {
            bs.emplace_back(s);
            cout << s << " is in B(S)!\n";
        }

        cout << "--------\n";
    }

    cout << "B(S): ";
    for (auto &elem: bs) {
        cout << elem << " ";
    }
    cout << "\n";
    cout << "\n";
}

std::vector<std::unordered_set<uint64_t>> MainController::divideParts(vector<std::unordered_set<uint64_t>> &rs_vec, vector<uint64_t> &bs) {
    // 建立并查集
    UnionFind unionFind;
    for (auto &elem: bs) {
        unionFind.makeSet(elem);
    }

    // 合并
    for (uint64_t i = 0; i < bs.size(); i++) {
        auto& rs1 = rs_vec[bs[i]];
        for (uint64_t j = i; j < bs.size(); j++) {
            auto& rs2 = rs_vec[bs[j]];
            bool intersect = !all_of(rs1.begin(),rs1.end(),
                                    [&rs2](uint64_t elem) {return rs2.find(elem) == rs2.end();});
            if(intersect){
                unionFind.unite(bs[i],bs[j]);
            }
        }
    }

    // 生成分区
    std::unordered_map<uint64_t, std::unordered_set<uint64_t>> classes_map;
    for (const auto& elem : bs) {
        uint64_t root = unionFind.find(elem);
        auto &aim_rs = rs_vec[elem];
        classes_map[root].insert(aim_rs.begin(),aim_rs.end());
//        cout<<"DEBUG: "<<root<<".insert("<<elem<<")\n";
    }

    std::vector<std::unordered_set<uint64_t>> parts;
    for (const auto& entry : classes_map) {
        parts.push_back(entry.second);
//        cout<<"DEBUG: "<<"parts.push_back entry size: "<<entry.second.size()<<"\n";
    }

    // 打印分区
    cout<<"Parts: \n";
    for(int i=0;i<parts.size();i++){
        cout<<"P"<<i<<": ";
        for(auto& elem: parts[i]){
            cout<<elem<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    return parts;
}
