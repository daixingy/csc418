#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  h = 0;
  s = 0;
  v = 0;

  //find maximum, minimum, and chroma component.
  double r_ = r/255;
  double g_ = g/255;
  double b_ = b/255;
  double l[] = {r_, g_, b_};
  double cmax = *std::max_element(l, l+3);
  double cmin = *std::min_element(l, l+3);
  double C = cmax - cmin;
  
  //calculating hue
  if(C == 0){
    h = 0;
  }else if(cmax == r_){
    h = 60*((g_-b_)/(C));
  }else if(cmax == g_){
    h = 60*((b_-r_)/C + 2);
  }else{
    h = 60*((r_-g_)/C + 4);
  }
  if(h < 0){
    h += 360;
  }
  //calculating saturation.
  if(cmax == 0){
    s = 0;
  }else{
    s = C/cmax;
  }
  //assign the value
  v = cmax;
  ////////////////////////////////////////////////////////////////////////////
}
