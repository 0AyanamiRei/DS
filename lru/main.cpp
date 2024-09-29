#include "lru.cpp"

int
main() {
  LRUCache* obj = new LRUCache(1);
  obj->put(2, 1);
  cout << obj->get(1) << endl;
  return 0;
}