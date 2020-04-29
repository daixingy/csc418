#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i = 0; i < height; i++){
  	for(int j = 0; j < width; j++){
  		//get the source and destination alpha value
  		double alphasrc = (double)B[j*4+i*width*4+3]/255.0;
  		double alphadest = (double)A[j*4+i*width*4+3]/255.0;
  		//get the source and destination rgb value
  		double rsrc = B[j*4+i*width*4];
  		double gsrc = B[j*4+i*width*4+1];
  		double bsrc = B[j*4+i*width*4+2];
  		double rdest = A[j*4+i*width*4];
  		double gdest = A[j*4+i*width*4+1];
  		double bdest = A[j*4+i*width*4+2];
  		//composition
  		double Asrc = alphasrc * (1 - alphadest);
  		double Adest = alphadest * (1 - alphasrc);
  		double Aboth = alphasrc * alphadest;
  		C[j*4+i*width*4] = Asrc * rsrc + Adest * rdest + Aboth * rdest;
  		C[j*4+i*width*4+1] = Asrc * gsrc + Adest * gdest + Aboth * gdest;
  		C[j*4+i*width*4+2] = Asrc * bsrc + Adest * bdest + Aboth * bdest;
  		C[j*4+i*width*4+3] = (alphasrc + alphadest*(1-alphasrc))*255;
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
