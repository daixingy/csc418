#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <Eigen/Geometry>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for(int i = 0; i < F.rows(); i++){
  	for(int j = 0; j < F.cols(); j++){
    Eigen::RowVector3d a, b, c, FN, VN(0, 0, 0);
    double area;
	  a = V.row(F(i, 0));
	  b = V.row(F(i, 1));
	  c = V.row(F(i, 2));
	  FN = triangle_area_normal(a, b, c);
		for(int k = 0; k < VF[F(i, j)].size(); k++){
		  Eigen::RowVector3d ahat, bhat, chat;
		  ahat = V.row(F(VF[F(i, j)][k], 0));
		  bhat = V.row(F(VF[F(i, j)][k], 1));
		  chat = V.row(F(VF[F(i, j)][k], 2));
		  if(FN.dot(((ahat-bhat).cross(ahat-chat)).normalized()) > cos(corner_threshold*M_PI/180.0)){
		  	area += ((ahat-bhat).cross(ahat-chat)).norm()/2.0;
		  	VN += triangle_area_normal(ahat, bhat, chat);
		  }
		}
    N.row(i*3+j) = (VN/area).normalized();
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
