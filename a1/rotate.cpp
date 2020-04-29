#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // if the input image is grayscle.
  if(num_channels != 3){
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        int rot = j*num_channels+i*height*num_channels;
        int inp = (height-i)*num_channels+j*width*num_channels;
        rotated[rot] = input[inp];
      }
    }
  }// if the input image is rgb.
  else{
  	for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        int rot = j*num_channels+i*height*num_channels;
        int inp = (height-i)*num_channels+j*width*num_channels;
        rotated[rot] = input[inp];
        rotated[rot+1] = input[inp+1];
        rotated[rot+2] = input[inp+2];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
