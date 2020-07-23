#pragma once

#include "point3d.h"
#include <Eigen/Dense>

class Point3dSph : public Point3d {
public:
  Point3dSph(double, double, double);
  Point3dSph(const Eigen::Vector3d &);
  Point3dSph(const Point3dSph &);

  double getR();
  double getTheta();
  double getPhi();

  void setR(double);
  void setTheta(double);
  void setPhi(double);
};
