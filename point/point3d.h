#pragma once

#include "../constants/constants.h"

#include <Eigen/Dense>

class Point3d {
public:
  // Constructors
  Point3d(double, double, double);
  Point3d(const Eigen::Vector3d &);
  Point3d(const Point3d &);

  // Getters & Setters
  Eigen::Vector3d getVector();
  double getX1();
  double getX2();
  double getX3();

  void setVector(const Eigen::Vector3d &v);
  void setX1(double);
  void setX2(double);
  void setX3(double);

  // Operators
  Point3d &operator=(Point3d);

  // Translations
  void T(const Eigen::Vector3d &); // inplace
  friend Point3d translate(const Point3d &, const Eigen::Vector3d &);

  Point3d &operator+=(Eigen::Vector3d const &);
  Point3d operator+(Eigen::Vector3d const &);

  Point3d &operator-=(Eigen::Vector3d const &);
  Point3d operator-(Eigen::Vector3d const &);

  // Access
  double operator[](size_t idx) const;

  Point3d &operator=(const Point3d &);

  // IO
  friend std::ostream &operator<<(std::ostream &, const Point3d &);

  // Utility
  void swap(Point3d &);
  friend void swap(Point3d &, Point3d &);

protected:
  double x1_ = 0;
  double x2_ = 0;
  double x3_ = 0;
};
