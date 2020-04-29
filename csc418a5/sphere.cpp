#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  V.resize((num_faces_u+1)*(num_faces_v+1),3);
  F.resize(num_faces_u*num_faces_v,4);
  UV.resize((num_faces_u+1)*(num_faces_v+1),2);
  UF.resize(num_faces_u*num_faces_v,4);
  NV.resize((num_faces_u+1)*(num_faces_v+1),3);
  NF.resize(num_faces_u*num_faces_v,4);

  double u, v, x, y, z;
  int index = 0;
  for(int i = 0; i < num_faces_v+1; i++){
    for(int j = 0; j < num_faces_u+1; j++){
      u = static_cast<double>(j)/num_faces_u;
      v = static_cast<double>(i)/num_faces_v;
      x = cos(v*M_PI - M_PI/2.0)*cos(2.0*u*M_PI - M_PI);
      y = cos(v*M_PI - M_PI/2.0)*sin(2.0*u*M_PI - M_PI);
      z = sin(v*M_PI - M_PI/2.0);
      V.row(index) = Eigen::RowVector3d(x, y, z);
      UV.row(index) = Eigen::RowVector2d(u, v);
      NV.row(index) = Eigen::RowVector3d(x, y, z);
      index++;
    }
  }

  index = 0;
  for(int i = 0; i < num_faces_v; i++){
    for(int j = 0; j < num_faces_u; j++){
      double idx1 = j + i*(num_faces_u+1);
      double idx3 = j + 1 + (i+1)*(num_faces_u+1);
      F.row(index) = Eigen::RowVector4i(idx1, idx1+1, idx3, idx3-1);
      UF.row(index) = Eigen::RowVector4i(idx1, idx1+1, idx3, idx3-1);
      NF.row(index) = Eigen::RowVector4i(idx1, idx1+1, idx3, idx3-1);
      index++;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
