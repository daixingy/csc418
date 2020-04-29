#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if(!ray_intersect_box(ray, this->box, min_t, max_t)){
    return false;
  }
  double tleft, tright;
  std::shared_ptr<Object> ldescendant, rdescendant;
  bool lefthit = this->left != NULL && this->left->ray_intersect(ray, min_t, max_t, tleft, ldescendant);
  bool righthit = this->right !=NULL && this->right->ray_intersect(ray, min_t, max_t, tright, rdescendant);

  if(lefthit &&  !ldescendant){
    ldescendant = left;
  }
  if(righthit &&  !rdescendant){
    rdescendant = right;
  }
  if(lefthit && righthit){
    if(tleft < tright){
      t = tleft;
      descendant = ldescendant;
    }else{
      t = tright;
      descendant = rdescendant;
    }
    return true;
  }else if(lefthit){
    t = tleft;
    descendant = ldescendant;
    return true;
  }else if(righthit){
    t = tright;
    descendant = rdescendant;
    return true;
  }else{
    return false;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

