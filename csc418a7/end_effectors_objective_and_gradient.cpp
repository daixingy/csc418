#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Skeleton s = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd pos = transformed_tips(s, b);
    return (pos - xb0).dot(pos - xb0);
  };

  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton s = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd pos = transformed_tips(s, b);
    Eigen::VectorXd grad = Eigen::MatrixXd::Zero(A.rows(), A.cols());
    Eigen::MatrixXd J;
    kinematics_jacobian(s, b, J);
    for(int bi = 0; bi < b.size(); bi++){
      for(int i=0;i<3;i++){
        grad += (pos(3*bi+i) - xb0(3*bi+i)) *  J.row(3*bi+i).transpose();
      }
    }
    return grad;
  };

  proj_z = [&](Eigen::VectorXd & A)
  {
    for (int i=0; i<skeleton.size(); i++) {
      for(int j = 0; j < 3; j++){
        A[3*i+j] = std::max(skeleton[i].xzx_min[j], std::min(skeleton[i].xzx_max[j], A[3*i+j]));
      }
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
