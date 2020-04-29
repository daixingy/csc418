#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double result = 0.0;
	for(int i = 0; i < 3; i++){
		double temp = fmax(box.min_corner[i] - query[i], query[i] - box.max_corner[i]);
		result += pow(fmax(temp, 0), 2);
	}

	return result;
  ////////////////////////////////////////////////////////////////////////////
}
