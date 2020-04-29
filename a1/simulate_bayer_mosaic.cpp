#include "simulate_bayer_mosaic.h"
#include <algorithm>
#include <cmath>

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i=0; i<height; i++){
  	for(int j=0; j<height; j++){
  		int col = std::fmod(i, 2);
  		int row = std::fmod(j, 2);
      //even colomn and even row, assign green
  		if(col==0 && row==0){
  			bayer[j+i*width] = rgb[j*3+i*width*3+1];
  		}//even colomn and odd row, assign blue
      else if(col==0 && row==1){
  			bayer[j+i*width] = rgb[j*3+i*width*3+2];
  		}//odd colomn and even row, assign red
      else if(col==1 && row==0){
  			bayer[j+i*width] = rgb[j*3+i*width*3];
  		}//even colomn and even row, assign green
      else{
  			bayer[j+i*width] = rgb[j*3+i*width*3+1];
  		}
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
