#include "demosaic.h"
#include <algorithm>
#include <cmath>

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i=0; i<height; i++){
  	for(int j=0; j<width; j++){
      //general  
      //other case green
      if(std::fmod(i, 2) == 0){
      	if(std::fmod(j, 2) == 0){
          rgb[j*3 + i*width*3] = (bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 2;
          rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 2] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width]) / 2;
        }//other case blue
        else if(std::fmod(j, 2) == 1){
	      rgb[j*3 + i*width*3] = (bayer[j - 1 + (i+1)*width] + bayer[j + 1 + (i-1)*width] + bayer[j - 1 + (i-1)*width] + bayer[j + 1 + (i+1)*width]) / 4;
	      rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width] + bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 4;
	      rgb[j*3 + i*width*3 + 2] = bayer[j + i*width];
	    }

      }else if(std::fmod(i, 2) == 1){
      	//other case green
      	if(std::fmod(j, 2) == 1){
          rgb[j*3 + i*width*3] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width]) / 2;
          rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 2] = (bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 2;
        }//other case red
        else if(std::fmod(j, 2) == 0){
          rgb[j*3 + i*width*3] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width] + bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 4;
          rgb[j*3 + i*width*3 + 2] = (bayer[j - 1 + (i+1)*width] + bayer[j + 1 + (i-1)*width] + bayer[j - 1 + (i-1)*width] + bayer[j + 1 + (i+1)*width]) / 4;
        }   
      }

      //first and last row and colon
      //first row
      else if(i == 0){
        //if green
        if(std::fmod(j, 2) == 0 && j > 0 && j < width-1){
          rgb[j*3 + i*width*3] = bayer[j + (i+1)*width];
          rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 2] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width]) / 2;
        }
        //if blue
        else if(std::fmod(j, 2) == 1 && j > 0 && j < width-1){
          rgb[j*3 + i*width*3] = (bayer[j - 1 + (i+1)*width] + bayer[j + 1 + (i+1)*width]) / 2;
          rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width] + bayer[j + (i+1)*width]) / 3;
          rgb[j*3 + i*width*3 + 2] = bayer[j + i*width];
        }
      }
      //first colon
      else if(j == 0){
        //if green
        if(std::fmod(i, 2) == 0 && i > 0 && i < height){
          rgb[j*3 + i*width*3] = (bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 2;
          rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 2] = bayer[j + 1 + i*width] / 2;
        }
        //if red
        else if(std::fmod(i, 2) == 1 && i > 0 && i < height){
          rgb[j*3 + i*width*3] = bayer[j + i*width];
          rgb[j*3 + i*width*3 + 1] = (bayer[j + 1 + i*width] + bayer[j + (i-1)*width] + bayer[j + (i+1)*width]) / 3;
          rgb[j*3 + i*width*3 + 2] = (bayer[j + 1 + (i-1)*width] + bayer[j + 1 + (i+1)*width]) / 2;
        }
      }
      //last row
      else if(i == height-1){
        //even height with green start
        if(std::fmod(height-1, 2) == 0){
          //if green
          if(std::fmod(j, 2) == 0 && j > 0 && j < width-1){
            rgb[j*3 + i*width*3] = bayer[j + (i-1)*width];
            rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
            rgb[j*3 + i*width*3 + 2] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width]) / 2;
          }
          //if blue
          else if(std::fmod(j, 2) == 1 && j > 0 && j < width-1){
            rgb[j*3 + i*width*3] = (bayer[j - 1 + (i-1)*width] + bayer[j + 1 + (i-1)*width]) / 2;
            rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width] + bayer[j + (i-1)*width]) / 3;
            rgb[j*3 + i*width*3 + 2] = bayer[j + i*width];
          }
        }
        //odd width with red start
        else{
          //if red
          if(std::fmod(j, 2) == 0 && j > 0 && j < width-1){
            rgb[j*3 + i*width*3] = bayer[j + i*width];
            rgb[j*3 + i*width*3 + 1] = (bayer[j + 1 + i*width] + bayer[j - 1 + i*width] + bayer[j + (i-1)*width]) / 3;
            rgb[j*3 + i*width*3 + 2] = (bayer[j + 1 + (i-1)*width] + bayer[j - 1 + (i-1)*width]) / 2;
          }
          //if green
          else if(std::fmod(j, 2) == 1 && j > 0 && j < width-1){
            rgb[j*3 + i*width*3] = (bayer[j - 1 + i*width] + bayer[j + 1 + i*width]) / 2;
            rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
            rgb[j*3 + i*width*3 + 2] = bayer[j + (i-1)*width];
          }
        }
      }
      //last colon
      else if(j == width-1){
        //even width start with green
        if(std::fmod(width-1, 2) == 0){
          //if green
          if(std::fmod(i, 2) == 0 && i > 0 && i < height-1){
            rgb[j*3 + i*width*3] = (bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 2;
            rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
            rgb[j*3 + i*width*3 + 2] = bayer[j - 1 + i*width];
          }
          //if red
          else if(std::fmod(i, 2) == 1 && i > 0 && i < height-1){
            rgb[j*3 + i*width*3] = bayer[j + i*width]; 
            rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 3;
            rgb[j*3 + i*width*3 + 2] = (bayer[j - 1 + (i-1)*width] + bayer[j - 1 + (i+1)*width]) / 2;
          }
        }
        //odd width start with blue
        else if(std::fmod(i, 2) == 0 && i > 0 && i < height-1){
            rgb[j*3 + i*width*3] = (bayer[j - 1 + (i-1)*width] + bayer[j - 1 + (i+1)*width]) / 2;
            rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 3;
            rgb[j*3 + i*width*3 + 2] = bayer[j + i*width];
          }
          //if green
          else if(std::fmod(j, 2) == 1 && j > 0 && j < width-1){
            rgb[j*3 + i*width*3] = bayer[j - 1 + i*width];
            rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
            rgb[j*3 + i*width*3 + 2] = (bayer[j + (i+1)*width] + bayer[j + (i-1)*width]) / 2;
          }
          
        //corner
	    //(0,0) must be green
	    if(i == 0 && j == 0){
	      rgb[j*3 + i*width*3] = bayer[j + (i+1)*width];
	      rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
	      rgb[j*3 + i*width*3 + 2] = bayer[j + 1 + i*width];
	    }
	    //(width, 0)
	    else if(i == 0 && j == width-1){
	      //even width-1 will be green
	      if(std::fmod(width-1, 2) == 0){
	        rgb[j*3 + i*width*3] = bayer[j + (i+1)*width];
	        rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
	        rgb[j*3 + i*width*3 + 2] = bayer[j - 1 + i*width];
	      }else{
            rgb[j*3 + i*width*3] = bayer[j - 1 + (i+1)*width];
	        rgb[j*3 + i*width*3 + 1] = (bayer[j - 1 + i*width] + bayer[j + (i+1)*width]) / 2;
	        rgb[j*3 + i*width*3 + 2] = bayer[j + i*width];
	      }
	    }
	    //(0, height)
	    else if(j == 0 && i == height-1){  
          //even height will be green
	      if(std::fmod(height-1, 2) == 0){
	        rgb[j*3 + i*width*3] = bayer[j + (i-1)*width];
	        rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
	        rgb[j*3 + i*width*3 + 2] = bayer[j + 1 + i*width];
	      }else{
	        rgb[j*3 + i*width*3] = bayer[j + i*width];
	        rgb[j*3 + i*width*3 + 1] = (bayer[j + (i-1)*width] + bayer[j + i*width - 1]) / 2;
	        rgb[j*3 + i*width*3 + 2] = bayer[j + 1 + (i-1)*width];
	      }
	    }
	    //(width, height)
	    else if(i == height-1 && j == width-1){
	      //even height even width or odd odd will be green
	      if(std::fmod(height-1, 2) == 0 && std::fmod(width-1, 2) == 0){
	        rgb[j*3 + i*width*3] = bayer[j + (i-1)*width];
	        rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
	        rgb[j*3 + i*width*3 + 2] = bayer[j - 1 + i*width];
	      }else if((std::fmod(height-1, 2) == 1 && std::fmod(width-1, 2) == 1)){
	        rgb[j*3 + i*width*3] = bayer[j - 1 + i*width];
	        rgb[j*3 + i*width*3 + 1] = bayer[j + i*width];
	        rgb[j*3 + i*width*3 + 2] = bayer[j + (i-1)*width];
	      }
	    }
      }
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
