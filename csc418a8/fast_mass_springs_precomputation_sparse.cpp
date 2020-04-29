#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv, C_ijv, M_ijv;
  Eigen::SparseMatrix<double> Q(V.rows() ,V.rows());
  r = Eigen::VectorXd::Zero(E.rows());
  M.resize(V.rows(), V.rows());
  C.resize(b.size(), V.rows());

  for (int i=0; i<E.rows(); i++) {
    r(i) = (V.row(E(i,0)) - V.row(E(i,1))).norm();
  }
  for (int j=0; j<V.rows(); j++) {
    M_ijv.emplace_back(j, j, m(j));
  }
  M.setFromTriplets(M_ijv.begin(),M_ijv.end());

  signed_incidence_matrix_sparse(V.rows(), E, A);
  for (int l=0; l<b.size(); l++) {
    C_ijv.emplace_back(l, b(l), 1);
  }
  C.setFromTriplets(C_ijv.begin(),C_ijv.end());

  double w = 1e10;
  Q = k * A.transpose() * A + 1/pow(delta_t,2) * M + w * C.transpose() * C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
