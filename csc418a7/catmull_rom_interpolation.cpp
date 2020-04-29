#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  // Reference: https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline.
  if(keyframes.empty()){
  	return Eigen::Vector3d(0, 0, 0);
  }
  t = std::fmod(t, keyframes.back().first);
  int i = 0;
  while(t > keyframes[i].first){
  	i++;
  }
  Eigen::Vector3d P0, P1, P2, P3;
  double t0, t1, t2, t3;
  if(i - 2 < 0 || i >= keyframes.size()-1){
    P0 = keyframes[i-1].second;
    P1 = keyframes[i].second;
    t0 = keyframes[i-1].first;
    t1 = keyframes[i].first;
    t = (t1 - t)/(t1 - t0);
    return t*P0 + (1-t)*P1;
  }else{
  	P0 = keyframes[i-2].second;
  	P1 = keyframes[i-1].second;
  	P2 = keyframes[i].second;
  	P3 = keyframes[i+1].second;

  	t0 = keyframes[i-2].first;
  	t1 = keyframes[i-1].first;
  	t2 = keyframes[i].first;
  	t3 = keyframes[i+1].first;

  	Eigen::Vector3d A1, A2, A3;
  	A1 = ((t1-t)/(t1-t0))*P0+((t-t0)/(t1-t0))*P1;
  	A2 = ((t2-t)/(t2-t1))*P1+((t-t1)/(t2-t1))*P2;
  	A3 = ((t3-t)/(t3-t2))*P2+((t-t2)/(t3-t2))*P3;

  	Eigen::Vector3d B1, B2, C;
  	B1 = ((t2-t)/(t2-t0))*A1+((t-t0)/(t2-t0))*A2;
  	B2 = ((t3-t)/(t3-t1))*A2+((t-t1)/(t3-t1))*A3;
  	C = ((t2-t)/(t2-t1))*B1+((t-t1)/(t2-t1))*B2;

  	return C;
  }
  /////////////////////////////////////////////////////////////////////////////
}
