#include "hsv_to_rgb.h"
#include <algorithm>
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Calculating the chroma and the imtermediate value X
  double c = v*s;
  double h_ = h/60.0;
  double x = c*(1 - std::fabs(std::fmod((h_), 2) - 1));
  
  double r_ = 0;
  double g_ = 0;
  double b_ = 0;

  if(0.0 <= h_ && h_ <= 1.0){
    r_ = c;
    g_ = x;
  }else if(1.0 < h_ && h_ <= 2.0){
    r_ = x;
    g_ = c;
  }else if(2.0 < h_ && h_ <= 3.0){
    g_ = c;
    b_ = x;
  }else if(3.0 < h_ && h_ <= 4.0){
    g_ = x;
    b_ = c;
  }else if(4.0 < h_ && h_ <= 5.0){
    r_ = x;
    b_ = c;
  }else if(5.0 < h_ && h_ <= 6.0){
    r_ = c;
    b_ = x;
  }
  // find R, G, and B by adding the same amount to each component
  double m = v-c;
  r = (r_ + m)*255;
  g = (g_ + m)*255;
  b = (b_ + m)*255;
  ////////////////////////////////////////////////////////////////////////////
}
