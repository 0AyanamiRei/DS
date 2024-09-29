#include <random>
#include <climits>
#include <iostream>

double randomDouble() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

struct SkiplistNode {
  int level;
  int key, val;
  SkiplistNode **forward;

  SkiplistNode()=default;

  SkiplistNode(int k, int v, int l, SkiplistNode *next = nullptr) : key(k), val(v), level(l) {
    forward = new SkiplistNode *[l + 1];
    for(int i = 0; i < l + 1 ; i ++) forward[i] = next;
  }

  ~SkiplistNode() {
    if (forward != NULL) delete[] forward;
  }
};

class skiplist {
public:
  skiplist(double);
  ~skiplist();

  auto randomLevel() -> int;
  auto find(const int& key) -> int;
  void insert(const int& key, const int& val);
  auto Delete(const int& key) -> bool;
  auto operator[](const int &key) -> int&; 

private:
  double p_;
  static const int MAXL = 32;
  static const int INVALID = INT32_MAX;

  SkiplistNode *head, *tail;
  int length;
  int level;
};
