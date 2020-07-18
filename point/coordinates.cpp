#include "coordinates.h"
#include "../constants/constants.h"

#include <Eigen/Dense>
#include <cmath>

Eigen::Vector3d toSph(const Eigen::Vector3d &v) {
  double x = v[0];
  double y = v[1];
  double z = v[2];

  double r = sqrt(x * x + y * y + z * z);
  double phi = atan(y / x);
  double theta = acos(z / r);
  return Eigen::Vector3d(r, phi, theta);
}

Eigen::Vector3d fromSph(const Eigen::Vector3d &v) {
  double r = v[0];
  double phi = v[1];
  double theta = v[2];

  double x = r * sin(theta) * cos(phi);
  double y = r * sin(theta) * sin(phi);
  double z = r * cos(theta);
  return Eigen::Vector3d(x, y, z);
}

Eigen::Vector3d toXYZ(const Eigen::Vector3d &v) { return fromSph(v); }
Eigen::Vector3d fromXYZ(const Eigen::Vector3d &v) { return toSph(v); }
