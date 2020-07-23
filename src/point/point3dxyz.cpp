#include "point3dxyz.h"
#include "point3d.h"
#include <Eigen/Dense>

double Point3dXYZ::getX() { return this->Point3d::getX1(); }
double Point3dXYZ::getY() { return this->Point3d::getX2(); }
double Point3dXYZ::getZ() { return this->Point3d::getX3(); }

void Point3dXYZ::setX(double c) { this->Point3d::setX1(c); }
void Point3dXYZ::setY(double c) { this->Point3d::setX2(c); }
void Point3dXYZ::setZ(double c) { this->Point3d::setX3(c); }
