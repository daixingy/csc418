#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  rgb = Eigen::Vector3d(0,0,0);
  double t;
  int hit_id;
  Eigen::Vector3d n, km;
  if(first_hit(ray, min_t, objects, hit_id, t, n)){
    km = objects[hit_id]->material->km;
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    if (num_recursive_calls <= 5){
      Ray reflected;
      Eigen::Vector3d final_rgb;
      reflected.origin = ray.origin+t*ray.direction;
      reflected.direction = reflect(ray.direction, n);
      raycolor(reflected, 0.001, objects, lights, num_recursive_calls+1, final_rgb);
      rgb += (km.array()*final_rgb.array()).matrix();
      return true;
    }else{
      return true;
    }
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
