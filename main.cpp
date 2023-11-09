#include "MainController.h"

#include <iostream>

using namespace std;

#include "UnionFind.h"

//void testUnionFind() {
//    cout << "testUnionFind\n";
//    unordered_set<uint64_t> bs = {2, 5, 7};
//    UnionFind uf(bs);
//    cout << "count: " << uf.count << ", parent vec: ";
//    for (auto &elem: uf.parent) {
//        cout << "(" << elem.first << ", " << elem.second << ") ";
//    }
//    cout << "\n";
//
//    uf.unite(2, 5);
//    cout << "count: " << uf.count << ", parent vec: ";
//    for (auto &elem: uf.parent) {
//        cout << "(" << elem.first << ", " << elem.second << ") ";
//    }
//    cout << "\n";
//}

int main() {
    cout << "Hello, World!" << endl;

//    testUnionFind();

    MainController mainController;
    mainController.start();

    return 0;
}


