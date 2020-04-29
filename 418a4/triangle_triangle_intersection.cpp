#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double t;
  Ray rayA1 = Ray(A0, A1-A0);
  Ray rayA2 = Ray(A1, A2-A1);
  Ray rayA3 = Ray(A2, A0-A2);
  Ray rayB1 = Ray(B0, B1-B0);
  Ray rayB2 = Ray(B1, B2-B1);
  Ray rayB3 = Ray(B2, B0-B2);

  bool AintersectB = ray_intersect_triangle(rayA1, B0, B1, B2, 0.0, 1.0, t) ||
                     ray_intersect_triangle(rayA2, B0, B1, B2, 0.0, 1.0, t) ||
                     ray_intersect_triangle(rayA3, B0, B1, B2, 0.0, 1.0, t);
  bool BintersectA = ray_intersect_triangle(rayB1, A0, A1, A2, 0.0, 1.0, t) ||
                     ray_intersect_triangle(rayB2, A0, A1, A2, 0.0, 1.0, t) ||
                     ray_intersect_triangle(rayB3, A0, A1, A2, 0.0, 1.0, t);

  return BintersectA || AintersectB;
  ////////////////////////////////////////////////////////////////////////////
}
