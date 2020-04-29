#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double nomi = ((point - ray.origin).dot(normal));
  double deno = (ray.direction.dot(normal));
  t = nomi/deno;

  if(t > min_t){
  	n = normal;
  	return true;
  }else{
  	return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

