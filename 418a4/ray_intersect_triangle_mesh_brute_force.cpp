#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double bound, t;
  bool hit = false;
  bound = std::numeric_limits<double>::max();
  for(int i = 0; i < F.rows(); i++){
    if(ray_intersect_triangle(ray, V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)), min_t, max_t, t) && t < bound){
      bound = t; 
      hit_t = t;
      hit_f = i;
      hit = true;
    }
  }
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
