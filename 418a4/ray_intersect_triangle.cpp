#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double a, b, c, d, e, f, g, h, i, j, k, l, deno;
  Eigen::Vector3d ans;

  a = A[0] - B[0]; 
  d = A[0] - C[0];
  g = ray.direction[0];
  b = A[1] - B[1];
  e = A[1] - C[1];
  h = ray.direction[1];
  c = A[2] - B[2];
  f = A[2] - C[2];
  i = ray.direction[2];
  j = A[0] - ray.origin[0];
  k = A[1] - ray.origin[1];
  l = A[2] - ray.origin[2];

  deno = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
  ans[0] = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/deno;
  ans[1] = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/deno;
  ans[2] = -((f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/deno);
  
  t = ans[2];
  if(t < min_t || t > max_t){
    return false;
  }else if(ans[1] < 0 || ans[1] > 1){
    return false;
  }else if(ans[0] < 0 || ans[0] > 1 - ans[1]){
    return false;
  }else{
    return true;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

