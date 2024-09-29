#include "bplus.hpp"
#include <iostream>
#include <vector>

using namespace BplusTree;

using std::cout, std::cin, std::endl;

int main() {
  BTree<int, int> tree(1);
  std::vector<int> records;
  cout << "test Bplus Tree Begin..." << endl;

  for(int i = 0; i < 10; i ++) {
    records.push_back(i);
    tree.Insert(i, i);
  }

  for(int i = 0; i < records.size(); i ++) {
    cout << tree.Query(records[i]) << endl;
  }

  cout << "test Bplus Tree End" << endl;
}