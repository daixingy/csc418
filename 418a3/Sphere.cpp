#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  double twoa, minusb, squareone, squaretwo, first, second;

	twoa = d.dot(d);
	minusb = -(d.dot(e-center));
	squareone = pow(d.dot(e-center), 2);
	squaretwo = (d.dot(d))*((e-center).dot(e-center) - pow(radius, 2));

	first = (minusb + sqrt(squareone - squaretwo))/twoa;
	second = (minusb - sqrt(squareone - squaretwo))/twoa;
  if(first > second){
  	if(first > min_t && min_t > second){
  		t = first;
  	}else{
  		t = second;
  	}
  }else{
  	if(second > min_t && min_t > first){
  		t = second;
  	}else{
  		t = first;
  	}
  }

  if(t > min_t){
  	n = (2*(e + t*d - center)).normalized();
  	return true;
  }else{
  	return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

