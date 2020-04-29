#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream outfile (filename, std::ofstream::binary);

  if(num_channels != 3){
    outfile << "P5" << "\n";
  }
  else{
    outfile << "P6" << "\n";
  }
  outfile << width << " " << height << "\n";
  outfile << "255" << "\n";
  outfile.write((char*)&data[0], data.size());
  outfile.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
