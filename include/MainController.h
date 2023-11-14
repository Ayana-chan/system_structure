//
// Created by DeathWind on 2023/11/9.
//

#ifndef SYSTEM_STRUCTURE_MAINCONTROLLER_H
#define SYSTEM_STRUCTURE_MAINCONTROLLER_H

#include "BinarySquareMatrix.h"

#include <unordered_set>
#include <unordered_map>

class MainController {
public:
    void start();

private:
    BinarySquareMatrix matrix;
    std::vector<std::unordered_set<uint64_t>> rs_vec, cs_vec;
    std::vector<uint64_t> bs;
    std::vector<std::unordered_set<uint64_t>> parts;
    // 每个part都是一个L队列，每个L都是一个集合
    std::vector<std::vector<std::unordered_set<uint64_t>>> level_vec;
    // 不分part地记录每个点对应的level
    std::unordered_map<uint64_t, int> reverse_level_map;
    // 被舍弃的点
    std::unordered_set<uint64_t> discarded_node;

    /**
     * 输入矩阵数据（边），将矩阵构造到成员变量中
     */
    void inputMatrixByEdge();

    /**
     * 输入矩阵数据（每个点的值），将矩阵构造到成员变量中
     */
    void inputMatrixByData();

    /**
     * 转为邻接矩阵
     */
    void transToReachableMatrix();

    /**
     * 计算起始集B(S)
     */
    void calculateBeginSet();

    /**
     * 划分区域
     */
    void divideParts();

    void divideLevel(std::vector<std::unordered_set<uint64_t>> &levels, const std::unordered_set<uint64_t> &part);

    /**
     * 删去强连接元素
     */
    void discardStrongLinkedNode();

    /**
     * 删去越级关系
     */
    void clearBypassedRelation();

    /**
     * 丢弃对角线上的关系
     */
    void clearSelfReachRelation();

    /**
     * 打印分区后的矩阵，是块对角矩阵
     */
    void printPartDividedMatrix();

    /**
     * 区域块三角矩阵
     */
    void printLevelDividedMatrixWithDiscard();
};


#endif //SYSTEM_STRUCTURE_MAINCONTROLLER_H
