#pragma once

#include <variant>  // for std::variant
#include <memory>   // for std::shared_ptr
#include <vector>
#include <cassert>


namespace BplusTree {

template<class K, class V>
struct BNode {
  int n_; /** 一个节点最多容纳的键值 */
  int size_;  /** 记录的键值 */

  bool isLeaf_; /** 是否叶子节点 */
  K *K_;
  V *V_;
  BNode **P_;

  BNode *parent_;

  BNode()=default;

  BNode (int n, bool leaf, int size = 0) : isLeaf_(leaf), size_(size) {
    n_ = n;
    parent_ = nullptr;
    this->K_ = new K(n_);
    this->V_ = new V[n_];
    this->P_ = new BNode<K,V>*[n_ + 1];
}
  
  ~BNode()  {
    delete K_;
    if(V_) delete []V_;
    if(P_) delete []P_;
}

};

template<class K, class V>
class BTree {

using NodePtr = BNode<K, V>*;

private:
  int n_;
  NodePtr root_;

  /** @note 1
  n = 3
  P0 K0 P1 K1  P2 K2  P3
  +--------------------+
  |p| 4 |p| 7 |p| 12 |p|
  +--------------------+ 
  规定拆分的值域区间是
  (-inf, 4) + [4, 7) + [7, 12) + [12, +inf)
  查询结果:
  key = 3,  i = 0
  key = 4,  i = 1
  key = 7,  i = 2
  key = 8,  i = 2
  key = 20, i = 3
  */

  /** @brief 获取值域含key的叶子节点 */
  auto GetBNode(K key, NodePtr& parent) -> NodePtr {
    BNode<K, V> *cursor = root_;
    while(!cursor->isLeaf_) {
      parent = cursor;

      /** @note 1*/
      int i;
      for(i = 0; i < cursor->size_ && key >= cursor->K_[i]; i ++);    
      cursor = cursor->P_[i];
    }
    return cursor;
  }


  void Insert2leaf(K key, V val, NodePtr& cursor) {
  assert(cursor->isLeaf_ == true);
  int i;
  for(i = 0; i < cursor->size_ && key >= cursor->K_[i]; i ++); 
  
  /** 挪动位置 K_[j-1]=key  K_[j-1] -> K_[j], V_[j-1] -> V_[j] */
  for(int j = cursor->size_; j > i ; j --) {
    cursor->K_[j] = cursor->K_[j-1];
    cursor->V_[j] = cursor->V_[j-1];
  }

  cursor->K_[i] = key;  
  cursor->V_[i] = val;
  cursor->size_++;
}
  
  /** @brief 将已满叶子节点分裂为两个左右叶子节点+临时内部节点 */
  void SplitLeaf(K key, V val, NodePtr& cursor, NodePtr& temp, NodePtr& Left, NodePtr& Right) {
  assert(cursor->isLeaf_ == true);

  int left_nums = (n_ + 1) / 2;
  int right_nums = n_ + 1 - (n_ + 1) / 2;
  Left  = new BNode<K,V>(n_, true, left_nums);
  Right = new BNode<K,V>(n_, true, right_nums);
  temp  = new BNode<K,V>(n_, false, 1);

  K Ktemp[n_+1];
  V Vtemp[n_+1];

  int i, j;
  for(i = 0; i < cursor->size_ && key >= cursor->K_[i]; i ++); 
  for(j = 0 ; j < i ; j ++) {
    Ktemp[j] = cursor->K_[j];
    Vtemp[j] = cursor->V_[j];
  }
  Ktemp[j] = key;
  Vtemp[j] = val;
  for(j++ ; j < cursor->size_ + 1 ; j ++) {
    Ktemp[j] = cursor->K_[j-1];
    Vtemp[j] = cursor->V_[j-1];
  }
  for(int k = 0; k < left_nums; k ++) {
    Left->K_[k] = Ktemp[k]; 
    Left->V_[k] = Vtemp[k];
  }
  for(int k = 0; k < right_nums; k ++) {
    Right->K_[k] = Ktemp[k+left_nums];
    Right->V_[k] = Vtemp[k + left_nums];
  }

  temp->P_[0] = Left;
  temp->P_[1] = Right;
  temp->K_[0] = Ktemp[(n_ + 1)/2];
  }


  /** @brief 正在修改的是分裂前叶子节点的父节点
   * @param[in] cursor 分裂前叶子节点的父节点, 当前阶段需要修改的节点
   * @param[in] Left 叶子节点分裂后得到的左儿子
   * @param[in] Right 叶子节点分裂后得到的左儿子
   * @param[in] temp 叶子节点分裂后临时创造的内部节点, 需要和`cursor`合并
  */
  void Insert2Inner(NodePtr& cursor, NodePtr& temp, NodePtr& Left, NodePtr& Right){
    /** case1 Left和Right由root_分裂而来 */
    if(cursor == nullptr) {
      root_->isLeaf_ = false;
      root_->size_ = temp->size_;
      for(int i = 0; i < root_->size_; ++ i) {
        root_->K_[i] = temp->K_[i];
        root_->P_[i] = temp->P_[i];
      }
      root_->P_[root_->size_] = temp->P_[root_->size_];
      Left->parent_ = Right->parent_ = root_; /** 分裂的时候要修改父节点指针 */
      return;
    }
    
    /** 现在我们只需要考虑往cursor插入两个指针和一个键值 */
    assert(cursor->isLeaf_ == false);

    /** case2 不满直接插入 */
    if(cursor->size_ < n_) {
      int i;
      for(i = 0; i < cursor->size_ && temp->K_[0] >= cursor->K_[i]; i ++);

      for(int j = cursor->size_; j > i ; --j) {
        cursor->K_[j] = cursor->K_[j-1];
        cursor->P_[j+1] = cursor->P_[j];
      }
      cursor->K_[i] = temp->K_[0];
      cursor->P_[i] = temp->P_[0];
      cursor->P_[i+1] = temp->P_[1];
      cursor->size_++;

      Left->parent_ = Right->parent_ = cursor;
      return ;
    }

    /** case3 已满, 继续向上插入(注意区别叶子节点的分裂) */
    int left_nums = (n_ + 1) / 2;
    int right_nums = n_ - (n_ + 1) / 2; /** <<<<<<< 和分裂叶子节点的区别 */

    K Ktemp[n_+1];
    NodePtr Ptemp[n_+2];

    int i, j;
    for(i = 0; i < cursor->size_ && temp->K_[0] >= cursor->K_[i]; i ++); 
    
    for(j = 0 ; j < i ; j ++) {
      Ktemp[j] = cursor->K_[j];
      Ptemp[j] = cursor->P_[j];
    }

    Ktemp[j] = temp->K_[0];
    Ptemp[j] = Left;
    Ptemp[j+1] = Right;

    for(j+=2; j < n_+1; j ++) {
      Ktemp[j] = cursor->K_[j-1];
      Ptemp[j+1] = cursor->P_[j];
    }
    //Ptemp[n_+1] = cursor->P_[n_];

    /** 创建分裂的节点并赋值 */
    BNode<K, V> *newLeft = new BNode<K, V>(n_, false, left_nums);
    BNode<K, V> *newRight = new BNode<K, V>(n_, false, right_nums);
    BNode<K, V> *newTemp = new BNode<K, V>(n_, false, 1);

    newTemp->K_[0] = Ktemp[n_ / 2];
    newTemp->P_[0] = newLeft;
    newTemp->P_[1] = newRight;


    for(i = 0; i < left_nums; i ++) {
      newLeft->K_[i] = Ktemp[i];
      newLeft->P_[i] = Ptemp[i]; 
    }
    newLeft->P_[i] = Ptemp[i];

    for(i ++; i < n_+2; i ++) {
      newRight->K_[i-left_nums-1] = Ktemp[i];
      newRight->P_[i-left_nums-1] = Ptemp[i]; 
    }
  /** <<<< 现在cursor分裂成了newLeft和newRight, 然后创建了一个newTemp需要往上传 */
  Insert2Inner(cursor->parent_, newTemp, newLeft, newRight);
  }

public:
  BTree()=delete;
  ~BTree()=default;
  BTree(int n) {
    assert(n > 0);
    n_ = n;
    root_ = nullptr;
  }

  /** @brief 接口: 插入 
 * 
 * 找到key所属值域的叶子节点, 会遇到以下事件
 * case1 树为空, 把`root_`初始化为第一个节点
 * case2 该叶子节点不满, 还可以容纳键值, 直接插入
 * case3 该叶子节点满了, 分裂成两个新的节点后再往上继续插入
 * 
 * @note case3 详细说明
 * 
 * 先在`Insert`中把叶子节点分裂成Left和Right叶子节点, 然后创建一
 * 个新的只含一个键值, 两个指针的非叶子节点, 指向左右儿子, 将这3个
 * 节点与我们追踪的父节点, 往上传即可, 剩下的工作交给调用函数来完成
 * 
 * 这个阶段不会修改节点的参数`isLeaf_`
*/
  void Insert(K key, V val){
    /** case 1 */
    if(root_ == nullptr) {
      root_ = new BNode<K, V>(n_, true);
      root_->K_[0] = key;
      root_->V_[0] = val;
      root_->size_++;
      return;
    }


    BNode<K,V> *parent = nullptr;
    BNode<K,V> *cursor = GetBNode(key, parent);
    cursor->parent_ = parent;

    /** case 2 不满, 直接插入 */
    if(cursor->size_ < n_) {
      Insert2leaf(key, val, cursor);
      return;
    }

    /** case3 需要分裂再插入 */
    BNode<K,V> *Left, *Right, *temp;
    SplitLeaf(key, val, cursor, temp, Left, Right);
    Insert2Inner(parent, temp, Left, Right);
  }

  auto Query(K key) -> V {
    BNode<K,V> *parent = nullptr;
    NodePtr node = GetBNode(key, parent);
    for(int i = 0; i < node->size_; i ++){
      if(node->K_[i] == key) {
        return node->V_[i];
      }
    }
    return 0;
  }
};

} // BplusTree namespace