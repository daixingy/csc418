#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
	for (int i=0; i<3; i++) {
		double l[] = {a[i], b[i], c[i]};
	  double max = *std::max_element(l, l+3);
	  double min = *std::min_element(l, l+3);
    B.min_corner[i] = fmin(B.min_corner[i], min);
    B.max_corner[i] = fmax(B.max_corner[i], max);
  } 
  ////////////////////////////////////////////////////////////////////////////
}


