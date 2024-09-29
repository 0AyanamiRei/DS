#include <unordered_map>
#include <iostream>

using namespace std;

struct LRUNode {
  int key, val;
  LRUNode* next, *prev;

  LRUNode(int key_, int val_) : key(key_), val(val_), next(nullptr), prev(nullptr) {}
};

class LRUCache {
private:
  int lru_size_, capacity_;
  LRUNode *head, *tail;
  std::unordered_map<int, LRUNode*> lru_map_;

public:
  LRUCache(int capacity);
  ~LRUCache();
  int get(int);
  void put(int, int);
  void add2Head(LRUNode*);
  LRUNode* removeNode(LRUNode*);
};
