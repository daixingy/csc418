#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  sqrD = std::numeric_limits<double>::max();
  double curr;
  for(int i = 0; i < points.rows(); i++){
  	curr = (query - points.row(i)).squaredNorm();
  	if(curr < sqrD){
  	  I = i;
  	  sqrD = curr;
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
