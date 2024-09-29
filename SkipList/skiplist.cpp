#include "skiplist.h"

using namespace std;

skiplist::skiplist(double p): p_(p) {
  level= length = 0; 
  tail = new SkiplistNode(INVALID, 0, 0);
  head = new SkiplistNode(INVALID, 0, MAXL, tail);
}

skiplist::~skiplist() {
  delete head;
  delete tail;
}

/** @brief 随机得到高度 
 * level=1, 1-p
 * level=2, p
 * level=n, p^(n-1)*(1-p)
 * level>=n, p^(n-1)
*/
auto skiplist::randomLevel() -> int {
  int level = 1;
  while(randomDouble() < p_ && level < MAXL) {
    level++;
  } 
  return level;
}

/** @brief 查询 */
auto skiplist::find(const int& key) -> int{
  SkiplistNode *p = head;
  
  // 找到该层最后一个键值小于 key 的节点，然后走向下一层
  for(int i = level; i >= 0; --i) {
    while(p->forward[i]->key < key) {
      p = p->forward[i];
    }
  }
  // 现在是小于，所以还需要再往后走一步
  p = p->forward[0];

  // 成功找到节点
  if (p->key == key) return p->val;

  // 节点不存在，返回 INVALID
  return tail->val;
}

/** @brief 插入 */
void skiplist::insert(const int& key, const int& val){
  SkiplistNode *update[MAXL + 1];

  SkiplistNode *p = head;
  for(int i = level; i >= 0; --i) {
    while(p->forward[i]->key < key) {
      p = p->forward[i];
    }
    update[i] = p;
  }
  p = p->forward[0];  

  // 若已存在则修改
  if(p->key == key) {
    p->val = val;
    return;
  }

  // 获取新节点的最大层数
  auto lv = randomLevel();
  if(lv > level) {
    lv = ++ level;
    update[lv] = head;
  }

  SkiplistNode *newNode = new SkiplistNode(key, val, lv);
  
  // 插入新节点
  for (int i = lv; i >= 0; --i) {
    p = update[i];
    newNode->forward[i] = p->forward[i];
    p->forward[i] = newNode;
  }

  ++length;
}

/** @brief 删除 */
auto skiplist::Delete(const int& key) -> bool{
  SkiplistNode *update[MAXL + 1];

  SkiplistNode *p = head;
  for(int i = level; i >= 0; --i) {
    while(p->forward[i]->key < key) {
      p = p->forward[i];
    }
    update[i] = p;
  }
  p = p->forward[0];

  if(p->key != key) return false;

  // 从最底层开始删除
  for(int i = 0; i <= level; ++i) {
    // 从层开始没有p
    if(update[i]->forward[i] != p) {
      break;
    }

    update[i]->forward[i] = p->forward[i];
  }

  // 回收空间
  delete p;

  // 删除节点可能导致最大层数减少
  while (level > 0 && head->forward[level] == tail) --level;

  --length;

  return true;
}

/** @todo 跳表随机访问优化 见OI-Wiki */
auto skiplist::operator[](const int &key) -> int&{
}

int main(){
  skiplist list(0.4);
  list.insert(3, 3);
  list.insert(5, 5);
  list.insert(11, 11);
  list.insert(8, 8);

  cout << list.find(11) << endl;
}