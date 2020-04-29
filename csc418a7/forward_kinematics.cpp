#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  std::function<Eigen::Affine3d(int)> recursion = [&skeleton, &recursion](int index)->Eigen::Affine3d{
  	if(skeleton[index].parent_index != -1){
  		Eigen::Affine3d Tpi, Tihat, Rihat;
  		Tpi = recursion(skeleton[index].parent_index);
  		Tihat = skeleton[index].rest_T;
  		Rihat = euler_angles_to_transform(skeleton[index].xzx);
  		return Tpi*Tihat*Rihat*(Tihat.inverse());
  	}else{
  		return Eigen::Affine3d::Identity();	
  	}
  };
  for(int i = 0; i < skeleton.size(); i++){
  	T[i] = recursion(i);
  }
  /////////////////////////////////////////////////////////////////////////////
}
