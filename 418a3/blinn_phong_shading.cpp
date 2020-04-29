#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d L, ks, kd, ka, d, q, p, second_n;
  double power, max_t, second_t;
  int second_hit_id;
  Ray shadow;

  ks = objects[hit_id]->material->ks;
  kd = objects[hit_id]->material->kd;
  ka = objects[hit_id]->material->ka;
  power = objects[hit_id]->material->phong_exponent;
    
  q = ray.origin+t*ray.direction;
  shadow.origin = q;
  L = ka*0.1;

  for(int i = 0; i < lights.size(); i++){
    lights[i]->direction(q, d, max_t);
    Eigen::Vector3d l = d;
    shadow.direction = l.normalized();
    Eigen::Vector3d v = -ray.direction.normalized();
    if(!(first_hit(shadow, 0.001, objects, second_hit_id, second_t, second_n)) || (second_t > max_t)){
      Eigen::Vector3d h = (l+v).normalized();
      double max1 = n.dot(l);
      double max2 = n.dot(h);
      if(max1 <= 0){
        max1 = 0;
      }
      max2 = std::pow(max2, power);
      L += (kd.array()*(lights[i]->I).array()).matrix()*max1+(ks.array()*(lights[i]->I).array()).matrix()*max2;
    }
  }
  return L;
  ////////////////////////////////////////////////////////////////////////////
}
