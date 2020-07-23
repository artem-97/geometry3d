#include "point3d.h"
#include "../constants/constants.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <Eigen/Dense>

// Constructors
Point3d::Point3d(double x1, double x2, double x3) : x1_(x1), x2_(x2), x3_(x3) {}

Point3d::Point3d(const Eigen::Vector3d &v) : x1_(v[0]), x2_(v[1]), x3_(v[2]) {}

Point3d::Point3d(const Point3d &other)
    : x1_(other.x1_), x2_(other.x2_), x3_(other.x3_) {}

// Getters & Setters
double Point3d::getX1() const { return x1_; }

double Point3d::getX2() const { return x2_; }

double Point3d::getX3() const { return x3_; }

CoordSystem Point3d::getCoordSystem() const { return coords_; }

Eigen::Vector3d Point3d::getVector() const {
  return Eigen::Vector3d(this->getX1(), this->getX2(), this->getX3());
}

void Point3d::setX1(double x) { x1_ = x; }

void Point3d::setX2(double x) { x2_ = x; }

void Point3d::setX3(double x) { x3_ = x; }

void Point3d::setCoordSystem(CoordSystem cs) { coords_ = cs; }

void Point3d::setVector(const Eigen::Vector3d &v) {
  setX1(v[0]);
  setX2(v[1]);
  setX3(v[2]);
}

// Utility
void Point3d::swap(Point3d &other) {
  std::swap(x1_, other.x1_);
  std::swap(x2_, other.x2_);
  std::swap(x3_, other.x3_);
}

void swap(Point3d &lhs, Point3d &rhs) { lhs.swap(rhs); }
// Operators
Point3d &Point3d::operator=(Point3d other) {
  this->swap(other);
  return *this;
}

// Translations
void Point3d::T(const Eigen::Vector3d &v) {
  x1_ += v[0];
  x2_ += v[1];
  x3_ += v[2];
}

Point3d translate(const Point3d &p, const Eigen::Vector3d &v) {
  auto tmp = p;
  tmp.T(v);
  return tmp;
}

Point3d &Point3d::operator+=(const Eigen::Vector3d &v) {
  this->T(v);
  return *this;
}

Point3d Point3d::operator+(const Eigen::Vector3d &v) {
  auto res = *this;
  return res += v;
}

Point3d &Point3d::operator-=(const Eigen::Vector3d &v) {
  this->T(-v);
  return *this;
}

Point3d Point3d::operator-(const Eigen::Vector3d &v) {
  auto res = *this;
  return res -= v;
}

// Access
const double &Point3d::operator[](size_t idx) const {
  assert(idx == 0 || idx == 1 || idx == 2);
  if (idx == 0)
    return x1_;
  else if (idx == 1)
    return x2_;
  else
    // idx == 2
    return x3_;
}

double &Point3d::operator[](size_t idx) {
  assert(idx == 0 || idx == 1 || idx == 2);
  if (idx == 0)
    return x1_;
  else if (idx == 1)
    return x2_;
  else
    // idx == 2
    return x3_;
}

// IO
std::ostream &operator<<(std::ostream &os, const Point3d &p) {
  std::cout << "Point: [" << p.x1_ << " " << p.x2_ << " " << p.x3_ << "] ";
  return os;
}

bool Point3d::isSPH() const { return coords_ == CoordSystem::XYZ; }

bool Point3d::isXYZ() const { return !this->isSPH(); }
