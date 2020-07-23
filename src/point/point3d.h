#pragma once

#include "../constants/constants.h"

#include <Eigen/Dense>
#include <compare>

class Point3d {
public:
  // Constructors
  Point3d(double, double, double);  // From x, y, z
  Point3d(const Eigen::Vector3d &); // From Eigen::Vector
  Point3d(const Point3d &);         // Copy constructor

  // Getters & Setters
  Eigen::Vector3d getVector() const; // Returns Eigen::Vector(x,y,z)
  double getX1() const;
  double getX2() const;
  double getX3() const;
  CoordSystem getCoordSystem() const;

  void setVector(const Eigen::Vector3d &v);

  void setX1(double);
  void setX2(double);
  void setX3(double);
  void setCoordSystem(CoordSystem);

  // Operators
  Point3d &operator=(Point3d);

  // Translations
  void T(const Eigen::Vector3d &); // inplace
  friend Point3d translate(const Point3d &, const Eigen::Vector3d &);

  // Affine geometry
  // Acts like our point is radius-vector with coords r(x1_,x_,x_3)
  Point3d &operator+=(Eigen::Vector3d const &);
  Point3d operator+(Eigen::Vector3d const &);

  Point3d &operator-=(Eigen::Vector3d const &);
  Point3d operator-(Eigen::Vector3d const &);

  // Access
  const double &operator[](size_t) const;
  double &operator[](size_t);

  // Eq
  auto operator<=>(const Point3d &) const = default;

  Point3d &operator=(const Point3d &);

  // IO
  friend std::ostream &operator<<(std::ostream &, const Point3d &);

  // Utility
  void swap(Point3d &);
  friend void swap(Point3d &, Point3d &);

protected:
  CoordSystem coords_ = CoordSystem::XYZ;

  double x1_ = 0;
  double x2_ = 0;
  double x3_ = 0;
};
