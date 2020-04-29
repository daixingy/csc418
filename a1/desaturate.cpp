#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i = 0; i < height; i++){
  	for(int j = 0; j < width; j++){
  		double r, g, b, h, s, v;
      //calculate the h, s, v value from inputs.
  		rgb_to_hsv((double)rgb[j*3 + i*width*3], (double)rgb[j*3 + i*width*3 + 1], (double)rgb[j*3 + i*width*3 + 2], h, s, v);
      //desaturate by the given factor
  		s = s*(1 - factor);
      //change back to rgb value with desaturation
  		hsv_to_rgb(h, s, v, r, g, b);

  		desaturated[j*3 + i*width*3] = (unsigned char)r;
  		desaturated[j*3 + i*width*3+1] = (unsigned char)g;
  		desaturated[j*3 + i*width*3+2] = (unsigned char)b;
  	}
  }
  ////////////////////////////////////////////////////////////////////////////
}
