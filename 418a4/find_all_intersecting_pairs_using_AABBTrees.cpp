#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // according to the given pesudocode in given readme
	std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> Q;
  if (box_box_intersect(rootA->box, rootB->box)){
    Q.emplace_back(rootA, rootB);
  }

  while (!Q.empty()){
    std::shared_ptr<Object> nodeA, nodeB;
    nodeA = Q.front().first;
    nodeB = Q.front().second;
    Q.pop_front();

    auto nodeA_ptr = std::dynamic_pointer_cast<AABBTree> (nodeA);
    auto nodeB_ptr = std::dynamic_pointer_cast<AABBTree> (nodeB);

    if(!nodeA_ptr && !nodeB_ptr){
      leaf_pairs.emplace_back(std::make_pair(nodeA, nodeB));
    }else if(!nodeA_ptr){
      if((nodeB_ptr->left != nullptr) && (box_box_intersect(nodeA->box, nodeB_ptr->left->box))){
        Q.emplace_back(nodeA, nodeB_ptr->left);
      }
      if((nodeB_ptr->right != nullptr) && (box_box_intersect(nodeA->box, nodeB_ptr->right->box))){
        Q.emplace_back(nodeA, nodeB_ptr->right);
      }
    }else if(!nodeB_ptr){
      if((nodeA_ptr->left != nullptr) && (box_box_intersect(nodeA_ptr->left->box, nodeB->box))){
        Q.emplace_back(nodeA_ptr->left, nodeB);
      }
      if((nodeA_ptr->right != nullptr) && (box_box_intersect(nodeA_ptr->right->box, nodeB->box))){
        Q.emplace_back(nodeA_ptr->right, nodeB);
      }
    }else{
      if((nodeA_ptr->left != nullptr) && (nodeB_ptr->left != nullptr) && (box_box_intersect(nodeA_ptr->left->box, nodeB_ptr->left->box))){
        Q.emplace_back(nodeA_ptr->left, nodeB_ptr->left);
      }
      if((nodeA_ptr->left != nullptr) && (nodeB_ptr->right != nullptr) && (box_box_intersect(nodeA_ptr->left->box, nodeB_ptr->right->box))){
        Q.emplace_back(nodeA_ptr->left, nodeB_ptr->right);
      }
      if((nodeA_ptr->right != nullptr) && (nodeB_ptr->right != nullptr) && (box_box_intersect(nodeA_ptr->right->box, nodeB_ptr->right->box))){
        Q.emplace_back(nodeA_ptr->right, nodeB_ptr->right);
      }
      if((nodeA_ptr->right != nullptr) && (nodeB_ptr->left != nullptr) && (box_box_intersect(nodeA_ptr->right->box, nodeB_ptr->left->box))){
        Q.emplace_back(nodeA_ptr->right, nodeB_ptr->left);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
