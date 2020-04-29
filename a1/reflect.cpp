#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // if the input image is grayscle.
  if(num_channels!=3){
  	for(int i=0; i<height;i++){
  		for(int j=0; j<width;j++){
        int ref = j*num_channels+i*width*num_channels;
        int inp = (width-j)*num_channels+i*width*num_channels;
  			reflected[ref] = input[inp];
  		}
  	}
  }// if the input image is rgb.
  else{
  	for(int i=0; i<height;i++){
  		for(int j=0; j<width;j++){
        int ref = j*num_channels+i*width*num_channels;
        int inp = (width-j)*num_channels+i*width*num_channels;
		  	reflected[ref] = input[inp];
		  	reflected[ref+1] = input[inp+1];
		  	reflected[ref+2] = input[inp+2];
  		}
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
