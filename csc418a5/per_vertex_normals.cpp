#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
#include <Eigen/Geometry>

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for(int i = 0; i < V.rows(); i++){
  	double area = 0;
    Eigen::RowVector3d VN(0, 0, 0);
  	for(int j = 0; j < VF[i].size(); j++){
  	  Eigen::RowVector3d a, b, c;
  	  a = V.row(F(VF[i][j], 0));
  	  b = V.row(F(VF[i][j], 1));
  	  c = V.row(F(VF[i][j], 2));
  	  area += ((a-b).cross(a-c)).norm()/2.0;
  	  VN += triangle_area_normal(a, b, c);
  	}
 	N.row(i) = (VN/area).normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}
