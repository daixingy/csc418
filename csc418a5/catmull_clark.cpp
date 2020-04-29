#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <Eigen/Geometry>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  SV.resize(0, 3);
  SF.resize(0, 4);
  std::unordered_map<int, Eigen::RowVector3d> FacePointMap;
  std::unordered_map<std::string, std::vector<int>> EdgeFacesMap;
  std::unordered_map<int, std::vector<int>> PointFacesMap, PointPointsMap;

  for(int i = 0; i < F.rows(); i++){
    Eigen::RowVector3d facepoint(0, 0, 0);
    for(int j = 0; j < F.cols(); j++){
      std::string key1 = std::to_string(F(i, j));
      std::string key2 = std::to_string(F(i, (j+1)%F.cols()));
      EdgeFacesMap[key1+"~~"+key2].push_back(i);
      EdgeFacesMap[key2+"~~"+key1].push_back(i);
      facepoint = facepoint + V.row(F(i, j));
      PointFacesMap[F(i, j)].push_back(i);
      PointPointsMap[F(i, j)].push_back(F(i, (j+1)%F.cols()));
    }
    FacePointMap[i] = facepoint/F.cols();
  }

  for(int i = 0; i < F.rows(); i++){
    for(int j = 0; j < F.cols(); j++){
      Eigen::RowVector3d aveFacePoint(0, 0, 0);
      Eigen::RowVector3d aveEdgePoint(0, 0, 0);
      for(int k = 0; k < PointFacesMap[F(i, j)].size(); k++){
        aveFacePoint += FacePointMap[PointFacesMap[F(i, j)][k]];
        Eigen::RowVector3d midpoint = V.row(F(i, j)) + V.row(PointPointsMap[F(i, j)][k]);
        aveEdgePoint += midpoint/2.0;
      }
      aveFacePoint = aveFacePoint/static_cast<double>(PointFacesMap[F(i, j)].size());
      aveEdgePoint = aveEdgePoint/static_cast<double>(PointPointsMap[F(i, j)].size());
      
      double n = PointFacesMap[F(i, j)].size();
      Eigen::RowVector3d newPosition = (aveFacePoint + 2*aveEdgePoint + (n-3)*V.row(F(i, j)))/n;

      Eigen::RowVector3d edgepoint1(0, 0, 0), edgepoint2(0, 0, 0);
      std::string key1 = std::to_string(F(i, j));
      std::string key2 = std::to_string(F(i, (j+1)%F.cols()));
      std::string key3 = std::to_string(F(i, (j-1+F.cols())%F.cols()));
      for(int k = 0; k < EdgeFacesMap[key1+"~~"+key2].size(); k++){
        edgepoint1 += FacePointMap[EdgeFacesMap[key1+"~~"+key2][k]];
      }
      edgepoint1 = (edgepoint1 + (V.row(F(i, j))+V.row(F(i, (j+1)%F.cols()))))/4.0;
      for(int k = 0; k < EdgeFacesMap[key1+"~~"+key3].size(); k++){
        edgepoint2 += FacePointMap[EdgeFacesMap[key1+"~~"+key3][k]];
      }
      edgepoint2 = (edgepoint2 + (V.row(F(i, j))+V.row(F(i, (j-1+F.cols())%F.cols()))))/4.0;

      Eigen::RowVector4i idxs(-1, -1, -1, -1);
      Eigen::MatrixXd newpoints;
      newpoints.resize(4,3);
      newpoints.row(0) = newPosition;
      newpoints.row(1) = edgepoint1;
      newpoints.row(2) = FacePointMap[i];
      newpoints.row(3) = edgepoint2;
      
      for(int l = 0; l < 4; l++){
        for(int h = 0; h < SV.rows(); h++){
          if(newpoints.row(l) == SV.row(h)){
            idxs[l] = h;
          }
        }
        if(idxs[l] == -1){
          SV.conservativeResize(SV.rows()+1 , 3);
          SV.row(SV.rows()-1) = newpoints.row(l);
          idxs[l] = SV.rows()-1;
        }
      }
      SF.conservativeResize(SF.rows()+1, 4);
      SF.row(SF.rows()-1) = idxs;
    }
  }
  if(num_iters == 1){
    return;
  }
  Eigen::MatrixXd newV = SV;
  Eigen::MatrixXi newF = SF;
  catmull_clark(newV, newF, num_iters-1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
