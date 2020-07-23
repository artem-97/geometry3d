#include "point3dsph.h"
#include "coordinates.h"
#include "point3d.h"
#include <Eigen/Dense>

Point3dSph::Point3dSph(double x, double y, double z) : Point3d(x, y, z) {
  Eigen::Vector3d v = this->getVector();
  v = toSph(v);

  x1_ = v[0];
  x2_ = v[1];
  x3_ = v[2];
}

Point3dSph::Point3dSph(const Eigen::Vector3d &e) : Point3d(e) {
  Eigen::Vector3d v = this->getVector();
  v = toSph(v);

  x1_ = v[0];
  x2_ = v[1];
  x3_ = v[2];
}

Point3dSph::Point3dSph(const Point3dSph &p) : Point3d(p.x1_, p.x2_, p.x3_) {
  Eigen::Vector3d v = this->getVector();
  v = toSph(v);

  x1_ = v[0];
  x2_ = v[1];
  x3_ = v[2];
}

double Point3dSph::getR() { return getX1(); }
double Point3dSph::getTheta() { return getX2(); }
double Point3dSph::getPhi() { return getX3(); }

void Point3dSph::setR(double c) { setX1(c); }
void Point3dSph::setPhi(double c) { setX2(c); }
void Point3dSph::setTheta(double c) { setX3(c); }
