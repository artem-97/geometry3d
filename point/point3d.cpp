#include "point3d.h"
#include <algorithm>
#include <iostream>

#include <Eigen/Dense>

// Constructors
Point3d::Point3d(double x1, double x2, double x3) : x1_(x1), x2_(x2), x3_(x3) {}

Point3d::Point3d(const Eigen::Vector3d &v) : x1_(v[0]), x2_(v[1]), x3_(v[2]) {}

Point3d::Point3d(const Point3d &other)
    : x1_(other.x1_), x2_(other.x2_), x3_(other.x3_) {}

// Getters & Setters
double Point3d::getX1() { return x1_; }

double Point3d::getX2() { return x2_; }

double Point3d::getX3() { return x3_; }

Eigen::Vector3d Point3d::getVector() {
  return Eigen::Vector3d(this->getX1(), this->getX2(), this->getX3());
}

void Point3d::setX1(double x) { x1_ = x; }

void Point3d::setX2(double x) { x2_ = x; }

void Point3d::setX3(double x) { x3_ = x; }

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

// IO
std::ostream &operator<<(std::ostream &os, const Point3d &p) {
  std::cout << "Point: [" << p.x1_ << " " << p.x2_ << " " << p.x3_ << "] ";
  return os;
}
