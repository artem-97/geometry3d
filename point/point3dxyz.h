#pragma once

#include "point3d.h"
#include <Eigen/Dense>

class Point3dXYZ : public Point3d {
public:
  Point3dXYZ(double, double, double);
  Point3dXYZ(const Eigen::Vector3d &);
  Point3dXYZ(const Point3dXYZ &);

  double getX();
  double getY();
  double getZ();

  void setX(double);
  void setY(double);
  void setZ(double);
};
