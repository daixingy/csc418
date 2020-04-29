#include "signed_incidence_matrix_dense.h"

void signed_incidence_matrix_dense(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::MatrixXd & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  A = Eigen::MatrixXd::Zero(E.rows(),n);
  for (int e=0; e<E.rows(); e++) {
  	for (int k=0; k<n; k++) {
  		if (k == E(e,0)) {
  			A(e,k) += 1.0;
  		}else if (k == E(e,1)) {
  			A(e,k) += -1.0;
  		}
  	}
  }  
  //////////////////////////////////////////////////////////////////////////////
}
