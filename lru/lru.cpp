#include "lru.h"


LRUCache::LRUCache(int capacity) : capacity_(capacity), lru_size_(0){
  // if(capacity <= 0){}
  head = new LRUNode(0,0);
  tail = new LRUNode(0,0);
  head->next = tail;
  tail->prev = head;
}

LRUCache::~LRUCache(){}


/**
 * @brief 根据`lru_map_`寻找对应的LRUNode*, 需要将本次访问的LRUNode放置在表头
*/
int
LRUCache::get(int key_) {
  if(!lru_map_.count(key_)) {
    return -1;
  }

  LRUNode* node = lru_map_[key_];
  removeNode(node);
  add2Head(node);

  return node->val;
}

void
LRUCache::put(int key_, int val_){
  if(!lru_map_.count(key_)) { /** 新节点 */
    LRUNode* temp = new LRUNode(key_, val_);
    lru_map_[key_] = temp;

    if(lru_size_ >= capacity_) { /** 需要驱逐 */
      LRUNode* remove_node = removeNode(tail->prev);
      lru_map_.erase(remove_node->key);
      delete remove_node;
    } else {
      lru_size_++;
    }

    add2Head(temp);
  }


  LRUNode* node = lru_map_[key_];
  node->val = val_;
  removeNode(node);
  add2Head(node);
}

void
LRUCache::add2Head(LRUNode *temp) {
  temp->next = head->next;
  head->next->prev = temp;
  head->next = temp;
  temp->prev = head;
}

LRUNode*
LRUCache::removeNode(LRUNode *temp) {
  temp->prev->next = temp->next;
  temp->next->prev = temp->prev;
  return temp;
}

