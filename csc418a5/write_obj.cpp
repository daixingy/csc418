#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream outfile (filename, std::ofstream::binary);
  for(int i = 0; i < V.rows(); i++){
    outfile << "v " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << "\n";
  }


  for(int i = 0; i < UV.rows(); i++){
    outfile << "vt " << UV(i, 0) << " " << UV(i, 1) << "\n";
  }

  for(int i = 0; i < NV.rows(); i++){
    outfile << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << "\n";
  }

  for(int i = 0; i < F.rows(); i++){
    outfile << "f ";
    for(int j = 0; j < F.cols(); j++){
      outfile << F(i, j)+1 << "/" << UF(i, j)+1 << "/" << NF(i, j)+1 << " ";
    }
    outfile << "\n";
  }
  outfile.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
