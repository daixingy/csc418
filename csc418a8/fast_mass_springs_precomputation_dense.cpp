#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());
  r = Eigen::VectorXd::Zero(E.rows());
  M = Eigen::MatrixXd::Zero(V.rows(),V.rows());
  C = Eigen::MatrixXd::Zero(b.size(), V.rows()); 
  for (int i=0; i<E.rows(); i++){
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }
  for (int j=0; j<M.rows(); j++){
    M(j, j) = m(j);
  }
  signed_incidence_matrix_dense(V.rows(), E, A);
  for (int l=0; l<C.rows(); l++){
    C(l, b(l)) = 1;
  }
  double w = 1e10;
  Q = k*A.transpose() * A + 1/(delta_t*delta_t) * M + w*C.transpose()*C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
