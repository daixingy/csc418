#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;
  double mini = std::numeric_limits<double>::max();
  Eigen::Vector3d curr_n;
  for(int i = 0; i < objects.size(); i++){
    if((*objects[i]).intersect(ray, min_t, t, n) && t<mini && min_t<mini){
      hit_id = i;
      mini = t;
      curr_n = n;
      hit = true;
    }
  }
  t = mini;
  n = curr_n;
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
