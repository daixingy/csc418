#include "fast_mass_springs_step_sparse.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::SparseMatrix<double>  & M,
  const Eigen::SparseMatrix<double>  & A,
  const Eigen::SparseMatrix<double>  & C,
  const Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd p, d, y, bhat;
  p = Ucur;
  d = Eigen::MatrixXd::Zero(E.rows(),3);
  for(int iter = 0;iter < 50;iter++) {
    for (int i=0; i<r.size(); i++) {
      d.row(i) = r(i) * (p.row(E(i,0)) - p.row(E(i,1))).normalized();
    }
    y = 1/pow(delta_t,2) * M * (2*Ucur - Uprev) + fext;
    double w = 1e10; 
    bhat = k * A.transpose() * d + y + w * C.transpose() * C * V;
    p = prefactorization.solve(bhat);
  }
  Unext = p;
  //////////////////////////////////////////////////////////////////////////////
}
