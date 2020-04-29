#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int size = objects.size();
	if(size == 0){
    this->left = NULL;
    this->right = NULL;
  }else if(size == 1){
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(this->left->box, this->box);
  }else{
    for(int i = 0; i < size; i++){
      insert_box_into_box(objects[i]->box, this->box);
    }

    int axis;
    double split;
    (this->box.max_corner-this->box.min_corner).maxCoeff(&axis);
    split = 0.5*(box.min_corner(axis)+box.max_corner(axis));

    std::vector<std::shared_ptr<Object>> leftpartition, rightpartition;
    for(int i = 0; i < size; i++){
      if(objects[i]->box.center()(axis)<split){
        leftpartition.emplace_back(objects[i]);
      }else{
        rightpartition.emplace_back(objects[i]);
      }
    }

    if(leftpartition.size() == 0 && rightpartition.size() != 0){
      leftpartition.emplace_back(rightpartition.back());
      rightpartition.pop_back();
    }else if(leftpartition.size() != 0 && rightpartition.size() == 0){
      rightpartition.emplace_back(leftpartition.back());
      leftpartition.pop_back();
    }

    this->left = std::make_shared<AABBTree>(leftpartition, a_depth+1);
    this->right = std::make_shared<AABBTree>(rightpartition, a_depth+1);
  }
  ////////////////////////////////////////////////////////////////////////////
}
