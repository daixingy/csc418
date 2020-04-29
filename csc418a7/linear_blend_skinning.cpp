#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U.resize(V.size(), 3);
  for (int i = 0; i < V.rows(); i++) {
  	Eigen::Vector4d vi = Eigen::Vector4d::Zero();
  	for (int j = 0; j < skeleton.size(); j++) {
      if (skeleton[j].weight_index != -1) {
        vi += T[j]*Eigen::Vector4d(V(i, 0), V(i, 1), V(i, 2), 1)*W(i, skeleton[j].weight_index);
  	  }
  	}
  	U(i, 0) = vi[0]/vi[3];
  	U(i, 1) = vi[1]/vi[3];
  	U(i, 2) = vi[2]/vi[3];
  }
  /////////////////////////////////////////////////////////////////////////////
}
