#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double x, y, z, xmin_t, ymin_t, zmin_t, xmax_t, ymax_t, zmax_t, tMax, tMin;
  x = 1/ray.direction[0];
  y = 1/ray.direction[1];
  z = 1/ray.direction[2];
 
  if(x >= 0){
  	xmin_t = (box.min_corner[0] - ray.origin[0])*x;
  	xmax_t = (box.max_corner[0] - ray.origin[0])*x;
  }else{
  	xmin_t = (box.max_corner[0] - ray.origin[0])*x;
  	xmax_t = (box.min_corner[0] - ray.origin[0])*x;
  }
  if(y >= 0){
  	ymin_t = (box.min_corner[1] - ray.origin[1])*y;
  	ymax_t = (box.max_corner[1] - ray.origin[1])*y;
  }else{
  	ymin_t = (box.max_corner[1] - ray.origin[1])*y;
  	ymax_t = (box.min_corner[1] - ray.origin[1])*y;
  }
  if(z >= 0){
  	zmin_t = (box.min_corner[2] - ray.origin[2])*z;
  	zmax_t = (box.max_corner[2] - ray.origin[2])*z;
  }else{
  	zmin_t = (box.max_corner[2] - ray.origin[2])*z;
  	zmax_t = (box.min_corner[2] - ray.origin[2])*z;
  }
  
  tMin = fmax(fmax(xmin_t, ymin_t), zmin_t);
  tMax = fmin(fmin(xmax_t, ymax_t), zmax_t);
  if (tMax < tMin) {
      return false;
  }
  
  if (fmin(max_t, tMax) < fmax(min_t, tMin)) {
      return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
