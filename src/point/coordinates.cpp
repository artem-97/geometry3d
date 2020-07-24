#include "coordinates.h"
#include "../constants/constants.h"

#include <Eigen/Dense>
#include <cassert>
#include <cmath>

Eigen::Vector3d toSph(const Eigen::Vector3d &v) {
  double x = v[0];
  double y = v[1];
  double z = v[2];

  double r = sqrt(x * x + y * y + z * z);
  double phi = atan2(y, x);
  double theta = acos(z / r);

  return Eigen::Vector3d(r, phi, theta);
}

Eigen::Vector3d fromSph(const Eigen::Vector3d &v) {
  double r = v[0]; // r -> (0; +inf)
  assert(r > 0);

  double phi = v[1]; // phi ->[0; 2pi)
  while (phi < 0) {
    phi += 2 * PI;
  }
  while (phi >= 2 * PI) {
    phi -= 2 * PI;
  }
  assert(phi >= 0 and phi < 2 * PI);

  double theta = v[2]; // theta -> [0; pi]
  while (theta < 0) {
    theta += 2 * PI;
  }
  while (theta > PI) {
    theta -= 2 * PI;
  }
  assert(theta >= 0 and theta <= PI);

  double x = r * sin(theta) * cos(phi);
  double y = r * sin(theta) * sin(phi);
  double z = r * cos(theta);
  return Eigen::Vector3d(x, y, z);
}

Eigen::Vector3d toXYZ(const Eigen::Vector3d &v) { return fromSph(v); }
Eigen::Vector3d fromXYZ(const Eigen::Vector3d &v) { return toSph(v); }
