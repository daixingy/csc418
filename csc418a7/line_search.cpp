#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double sigma = max_step;
  for(int i = 0; i < 20; i++){
     Eigen::VectorXd new_z = z - sigma*dz;
     proj_z(new_z);
     if (f(z) > f(new_z)) {
        return sigma;
     }
     sigma = sigma/2;
  }
  return sigma;
  /////////////////////////////////////////////////////////////////////////////
}
