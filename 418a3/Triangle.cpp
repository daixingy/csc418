#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::MatrixXd mat(3, 3);
  mat(0,0) = std::get<0>(corners)[0] - std::get<1>(corners)[0];
  mat(0,1) = std::get<0>(corners)[0] - std::get<2>(corners)[0];
  mat(0,2) = ray.direction[0];
  mat(1,0) = std::get<0>(corners)[1] - std::get<1>(corners)[1];
  mat(1,1) = std::get<0>(corners)[1] - std::get<2>(corners)[1];
  mat(1,2) = ray.direction[1];
  mat(2,0) = std::get<0>(corners)[2] - std::get<1>(corners)[2];
  mat(2,1) = std::get<0>(corners)[2] - std::get<2>(corners)[2];
  mat(2,2) = ray.direction[2];

  Eigen::Vector3d ori(std::get<0>(corners)[0] - ray.origin[0], std::get<0>(corners)[1] - ray.origin[1], std::get<0>(corners)[2] - ray.origin[2]);
  Eigen::Vector3d ans = mat.colPivHouseholderQr().solve(ori);
  t = ans[2];

  if(t<min_t){
  	return false;
  }else if(ans[1] < 0 || ans[1] > 1){
  	return false;
  }else if(ans[0] < 0 || ans[0] > 1 - ans[1]){
  	return false;
  }else{
  	Eigen::Vector3d u = ray.origin + t * ray.direction - std::get<0>(corners);
  	Eigen::Vector3d v = ray.origin + t * ray.direction - std::get<1>(corners);
  	n = u.cross(v).normalized();
  	return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}


