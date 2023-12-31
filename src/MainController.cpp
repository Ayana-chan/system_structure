//
// Created by DeathWind on 2023/11/9.
//

#include "MainController.h"
#include "UnionFind.h"

#include <iostream>
#include <algorithm>

using namespace std;

void MainController::start() {
//    inputMatrixByEdge();
    inputMatrixByData();
    transToReachableMatrix();

    cout << "*** 1. Divide Parts\n";
    calculateBeginSet();
    divideParts();
    printPartDividedMatrix();

    cout << "*** 2. Divide Levels\n";
    level_vec.resize(parts.size());
    for (int i = 0; i < parts.size(); i++) {
        cout << "-- Part " << i << "'s Level: \n";
        divideLevel(level_vec[i], parts[i]);
    }
    cout << "\n";
    cout << "Level Divided Matrix: \n";
    printLevelDividedMatrixWithDiscard();

    cout << "*** 3. Get Skeleton Matrix\n";
    discardStrongLinkedNode();
    cout << "-- After discard strong linked node: \n";
    printLevelDividedMatrixWithDiscard();
    clearBypassedRelation();
    cout << "-- After clear bypassed relation: \n";
    printLevelDividedMatrixWithDiscard();
    clearSelfReachRelation();
    cout << "-- After clear self reach relation: \n";
    cout << "Success Get Skeleton Matrix: \n";
    printLevelDividedMatrixWithDiscard();
}

void MainController::inputMatrixByEdge() {
    cout << "Please Input Matrix by Edge.\n";
    cout << "Example:\n node_num edge_num\n from1 to1\n from2 to2\n";
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
        if (from >= nodeNum || to >= nodeNum) {
            throw invalid_argument("Invalid Edge.");
        }
        data[from][to] = 1;
    }

    matrix = BinarySquareMatrix(data);

    //打印矩阵
    cout << "\n";
    cout << "Get Matrix: \n";
    cout << matrix;
    cout << "\n";
}

void MainController::inputMatrixByData() {
    cout << "Please Input Matrix by Data.\n";
    cout << "Example:\n node_num\n p00 p01\n p10 p11\n";
    cout << "Notice: index start with 0\n";

    uint64_t nodeNum;
    cin >> nodeNum;
    auto data(vector<vector<char>>(nodeNum, vector<char>(nodeNum, 0)));

    int input;
    for (int r = 0; r < nodeNum; r++) {
        for (int c = 0; c < nodeNum; c++) {
            cin >> input;
            if (!(input == 0 || input == 1)) {
                throw invalid_argument("Matrix data can only be 0 or 1.");
            }
            data[r][c] = static_cast<char>(input);
        }
    }

    matrix = BinarySquareMatrix(data);

    //打印矩阵
    cout << "\n";
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

void MainController::calculateBeginSet() {
    rs_vec.resize(matrix.get_size());
    cs_vec.resize(matrix.get_size());
    bs.clear();

    cout << "--------\n";
    for (uint64_t s = 0; s < matrix.get_size(); s++) {
        auto &rs = rs_vec[s];
        rs = matrix.calculateRs(s);
        cout << "R(" << s << "): ";
        for (const auto &elem: rs_vec[s]) {
            cout << elem << " ";
        }
        cout << "\n";

        auto as = matrix.calculateAs(s);
        cout << "A(" << s << "): ";
        for (const auto &elem: as) {
            cout << elem << " ";
        }
        cout << "\n";

        auto &cs = cs_vec[s];
        cs = matrix.calculateCs_straight(s);
        cout << "C(" << s << "): ";
        for (const auto &elem: cs) {
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

void MainController::divideParts() {
    // 建立并查集
    UnionFind unionFind;
    for (auto &elem: bs) {
        unionFind.makeSet(elem);
    }

    // 合并
    for (uint64_t i = 0; i < bs.size(); i++) {
        auto &rs1 = rs_vec[bs[i]];
        for (uint64_t j = i; j < bs.size(); j++) {
            auto &rs2 = rs_vec[bs[j]];
            bool intersect = !all_of(rs1.begin(), rs1.end(),
                                     [&rs2](uint64_t elem) { return rs2.find(elem) == rs2.end(); });
            if (intersect) {
                unionFind.unite(bs[i], bs[j]);
            }
        }
    }

    // 生成分区
    std::unordered_map<uint64_t, std::unordered_set<uint64_t>> classes_map;
    for (const auto &elem : bs) {
        uint64_t root = unionFind.find(elem);
        auto &aim_rs = rs_vec[elem];
        classes_map[root].insert(aim_rs.begin(), aim_rs.end());
//        cout<<"DEBUG: "<<root<<".insert("<<elem<<")\n";
    }
    for (const auto &entry : classes_map) {
        parts.push_back(entry.second);
//        cout<<"DEBUG: "<<"parts.push_back entry size: "<<entry.second.size()<<"\n";
    }

    // 打印分区
    cout << "Parts: \n";
    for (int i = 0; i < parts.size(); i++) {
        cout << "P" << i << ": ";
        for (auto &elem: parts[i]) {
            cout << elem << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void MainController::divideLevel(vector<std::unordered_set<uint64_t>> &levels, const unordered_set<uint64_t> &part) {
    int level_count = 0;
    // 尚未被划分等级的点
    auto rest_node = part;

    while (!rest_node.empty()) {
//        cout<<"DEBUG: calculate level "<<level_count<<"\n";
        unordered_set<uint64_t> new_level;
        // 找出所有cs=rs（无视discarded和非本part的点）的点
        for (auto &elem: part) {
            // 点本身已经分配过了
            if (rest_node.count(elem) == 0) {
                continue;
            }

//            cout<<"DEBUG: check node: "<<elem<<"\n";
            auto cs = cs_vec[elem];
            auto rs = rs_vec[elem];

            //剔除不考虑的点
            auto it = cs.begin();
            while (it != cs.end()) {
                if (rest_node.count(*it) == 0) {
//                    cout<<"DEBUG: cs discard "<< *it <<"\n";
                    it = cs.erase(it);
                } else {
                    it = next(it);
                }
            }
            it = rs.begin();
            while (it != rs.end()) {
                if (rest_node.count(*it) == 0) {
//                    cout<<"DEBUG: rs discard "<< *it <<"\n";
                    it = rs.erase(it);
                } else {
                    it = next(it);
                }
            }

            //检验相等
            if (cs == rs) {
//                cout<<"DEBUG: pass "<<elem<<"\n";
                new_level.insert(elem);
                reverse_level_map.insert({elem, level_count});
            }
        }

        // 丢弃已分配的点
        for (auto &elem: new_level) {
            rest_node.erase(elem);
        }

        // 打印
        cout << "Level " << level_count << ": ";
        for (auto &elem: new_level) {
            cout << elem << " ";
        }
        cout << "\n";

        levels.emplace_back(move(new_level));
        ++level_count;
    }
}

void MainController::discardStrongLinkedNode() {
    //由于不同part之间不可能有强连接要素，因此可以全部暴力遍历
    //但此处依然“节约”一下性能，即使计算量依然翻倍了
    for(auto& _part: parts){
        for(auto& r: _part){
            for(auto& c:_part){
                if(r == c){
                    continue;
                }
                if(matrix[r][c] == 1 && matrix[c][r] == 1){
                    auto& to_discard = max(r,c);
                    if(discarded_node.count(to_discard) > 0){
                        continue;
                    }
                    cout<<"Strong Linked Between "<<r<<" & "<<c<<", discard "<<to_discard<<"\n";
                    discarded_node.insert(to_discard);
                }
            }
        }
    }
}

void MainController::clearBypassedRelation() {
    //不存在从高到低的越级关系
    for (auto &r_pair: reverse_level_map) {
        auto &r = r_pair.first;
        auto &r_level = r_pair.second;
        for (auto &c_pair: reverse_level_map) {
            auto &c = c_pair.first;
            auto &c_level = c_pair.second;
//          cout<<"DEBUG: r_level: "<<r_level<<", c_level: "<<c_level<<"\n";
            if (matrix[r][c] == 1 && abs(r_level - c_level) > 1) {
                cout<<"Clear Bypassed Relation ("<<r<<", "<<c<<")\n";
                matrix[r][c] = 0;
            }
        }
    }
}

void MainController::clearSelfReachRelation() {
    for (int i = 0; i < matrix.get_size(); i++) {
        matrix[i][i] = 0;
    }
}

void MainController::printPartDividedMatrix() {
    cout << "Part Divided Matrix: \n";
    cout << "\\   ";
    for (auto &pc: parts) {
        for (auto &nodec: pc) {
            if (nodec < 10) {
                cout << nodec << "  ";
            } else {
                cout << nodec << " ";
            }
        }
        cout << "  "; //part竖分界线
    }
    cout << "\n";

    for (auto &pr: parts) {
        for (auto &noder: pr) {
            if (noder < 10) {
                cout << noder << "  |";
            } else {
                cout << noder << " |";
            }
            for (auto &pc: parts) {
                for (auto &nodec: pc) {
                    cout << static_cast<int>(matrix[noder][nodec]) << "  ";
                }
                cout << ".  "; //part竖分界线
            }
            cout << "\n";
        }

        //part横分界线
        cout << "    ";
        for (int _i = 0; _i < matrix.get_size() + parts.size(); _i++) {
            cout << ".  ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void MainController::printLevelDividedMatrixWithDiscard() {
    // 计算横分界线长度
    uint64_t horizontal_len = matrix.get_size() + parts.size() - discarded_node.size();
//    for (auto &p: level_vec) {
//        horizontal_len += p.size();
//    }

    cout << "\\       ";
    for (auto &partc: level_vec) {
        for (auto &levelc: partc) {
            for (auto &nodec: levelc) {
                if (discarded_node.count(nodec) > 0) {
                    continue;
                }
                if (nodec < 10) {
                    cout << nodec << "  ";
                } else {
                    cout << nodec << " ";
                }
            }
//            cout << "   "; //level竖分界线
        }
        cout << "   "; //part竖分界线
    }
    cout << "\n";

    for (auto &partr: level_vec) {
        for (auto &levelr: partr) {
            for (auto &noder: levelr) {
                if (discarded_node.count(noder) > 0) {
                    continue;
                }
                auto& cur_level = reverse_level_map[noder];
                cout<<"L"<<cur_level<<": ";
                if (noder < 10) {
                    cout << noder << "  |";
                } else {
                    cout << noder << " |";
                }
                for (auto &partc: level_vec) {
                    for (auto &levelc: partc) {
                        for (auto &nodec: levelc) {
                            if (discarded_node.count(nodec) > 0) {
                                continue;
                            }
                            cout << static_cast<int>(matrix[noder][nodec]) << "  ";
                        }
//                        cout << ".  "; //level竖分界线
                    }
                    cout << "|  "; //part竖分界线
                }
                cout << "\n";
            }

            //level横分界线
//            cout << "    ";
//            for (int _i = 0; _i < horizontal_len; _i++) {
//                cout << ".  ";
//            }
//            cout << "\n";
        }

        //part横分界线
        cout << "        ";
        for (int _i = 0; _i < horizontal_len; _i++) {
            cout << "-  ";
        }
        cout << "\n";
    }
    cout << "\n";
}




