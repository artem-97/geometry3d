#include "coordinates.h"
#include "point3d.h"
#include <Eigen/Dense>
#include <iostream>

int main() {
  Eigen::Vector3d v1(1, 2, 3);
  Eigen::Vector3d v2(4, 5, 6);
  Point3d p1(v1);
  Point3d p2(v2);
  auto p3(p2);

  std::cout << p1 + v2 << '\n';
  std::cout << p1 - v2 << '\n';
  std::cout << p3 - v2 << '\n';

  std::cout << v1 << '\n';
  std::cout << toSph(v1) << '\n';
  std::cout << toXYZ(toSph(v1)) << '\n';
}
