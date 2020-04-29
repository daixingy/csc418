#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
	ray.origin = camera.e;

	double ui, vj, md, d1, d2, d3;

	ui = camera.width*(j+0.5)/width-camera.width/2;
	vj = -camera.height*(i+0.5)/height+camera.height/2;
	md = -camera.d;

	d1 = camera.u[0]*ui+camera.v[0] * vj+camera.w[0]*md;
  d2 = camera.u[1]*ui+camera.v[1] * vj+camera.w[1]*md;
  d3 = camera.u[2]*ui+camera.v[2] * vj+camera.w[2]*md;

  Eigen::Vector3d direct(d1, d2, d3);
  ray.direction = direct;
  ////////////////////////////////////////////////////////////////////////////
}
