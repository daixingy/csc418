#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i = 0; i < height; i++){
  	for(int j = 0; j < width; j++){
  		double r, g, b, h, s, v;

      //calculate the h, s, v value from inputs.
  		rgb_to_hsv((double)rgb[j*3 + i*width*3], (double)rgb[j*3 + i*width*3 + 1], (double)rgb[j*3 + i*width*3 + 2], h, s, v);
      //hue shift
  		h = std::fmod(h+shift+360, 360);
      //change back to rgb value with shifted hue
  		hsv_to_rgb(h, s, v, r, g, b);

  		shifted[j*3 + i*width*3] = (unsigned char)r;
  		shifted[j*3 + i*width*3+1] = (unsigned char)g;
  		shifted[j*3 + i*width*3+2] = (unsigned char)b;
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
