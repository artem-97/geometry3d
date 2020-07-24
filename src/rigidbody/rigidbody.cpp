#include "rigidbody.h"
#include "../constants/constants.h"

#include <Eigen/Dense>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Constructors

RigidBody::RigidBody(const Points &points) : points_(points) {}
RigidBody::RigidBody(const RigidBody &other) : points_(other.points_) {}

// Operator=
RigidBody &RigidBody::operator=(RigidBody other) {
  this->swap(other);
  return *this;
}

// Utility
void RigidBody::swap(RigidBody &other) {
  assert(other.points_.size() == points_.size());
  std::swap(this->points_, other.points_);
}

void swap(RigidBody &lhs, RigidBody &rhs) { lhs.swap(rhs); }

// Getters / Setters
RigidBody::Points RigidBody::getPoints() const { return points_; }

void RigidBody::setPoints(RigidBody::Points pts) {
  assert(pts.size() == points_.size());
  points_ = std::move(pts);
}

// Translations
void RigidBody::moveX(double ts) {
  Eigen::Vector3d dx(ts, 0, 0);
  std::for_each(points_.begin(), points_.end(),
                [&](RigidBody::Point &point) { std::get<1>(point) += dx; });
}

void RigidBody::moveY(double ts) {
  Eigen::Vector3d dx(0, ts, 0);
  std::for_each(points_.begin(), points_.end(),
                [&](RigidBody::Point &point) { std::get<1>(point) += dx; });
}

void RigidBody::moveZ(double ts) {
  Eigen::Vector3d dx(0, 0, ts);
  std::for_each(points_.begin(), points_.end(),
                [&](RigidBody::Point &point) { std::get<1>(point) += dx; });
}

void RigidBody::moveTo(Point3d R) {
  moveX(R[0]);
  moveY(R[1]);
  moveZ(R[2]);
}

// COM

Eigen::Vector3d RigidBody::getCenterOfMass() const {
  double M = 0.;
  Eigen::Vector3d rm(0., 0., 0.);
  for (int i = 0; i < points_.size(); i++) {
    auto rm_i = std::get<1>(points_[i]).getVector();
    double m = std::get<0>(points_[i]);
    rm_i *= m;

    rm += rm_i;
    M += m;
  }
  assert(M != 0);
  Eigen::Vector3d R = rm / M;
  return R;
}

// switch to the center of mass ref.
void RigidBody::toCOMRef() {
  Eigen::Vector3d R = this->getCenterOfMass();
  Eigen::Vector3d Rto = -R;
  this->moveTo(Rto);
}

// Rotations
void ROTATION_ASSERT(const RigidBody &rb1, const RigidBody &rb2) {
  assert(rb1.points_.size() == rb2.points_.size());
  size_t i = 0;
  while (i < rb1.points_.size()) {
    double old_norm = std::get<1>(rb1.points_[i]).getVector().norm();
    double new_norm = std::get<1>(rb2.points_[i]).getVector().norm();
    if (abs(old_norm - new_norm) > old_norm) {
      std::cout << "OLD:" << old_norm << " NEW:" << new_norm << " idx:" << i
                << '\n';
      break;
    }
    ++i;
  }
  assert(i == rb1.points_.size());
}

void RigidBody::rotateX(double phi) {
  auto old_rb(*this);
  std::for_each(points_.begin(), points_.end(), [&](RigidBody::Point &point) {
    double &x = std::get<1>(point)[0];
    double &y = std::get<1>(point)[1];
    double &z = std::get<1>(point)[2];
    x = x;
    y = (y * cos(phi) - z * sin(phi));
    z = (y * sin(phi) + z * cos(phi));
  });
  ROTATION_ASSERT(*this, old_rb);
}

void RigidBody::rotateY(double phi) {
  auto old_rb(*this);
  std::for_each(points_.begin(), points_.end(), [&](RigidBody::Point &point) {
    double &x = std::get<1>(point)[0];
    double &y = std::get<1>(point)[1];
    double &z = std::get<1>(point)[2];
    x = x * cos(phi) + z * sin(phi);
    y = y;
    z = -x * sin(phi) + z * cos(phi);
  });
  ROTATION_ASSERT(*this, old_rb);
}

void RigidBody::rotateZ(double phi) {
  auto old_rb(*this);
  std::for_each(points_.begin(), points_.end(), [&](RigidBody::Point &point) {
    double &x = std::get<1>(point)[0];
    double &y = std::get<1>(point)[1];
    double &z = std::get<1>(point)[2];
    x = x * cos(phi) - y * sin(phi);
    y = y * sin(phi) + z * cos(phi);
    z = z;
  });
  ROTATION_ASSERT(*this, old_rb);
}

void RigidBody::rotateR(Eigen::Vector3d c, double phi) {
  c.normalize();
  for (int i = 0; i < points_.size(); i++) {
    auto xyz = points_[i].second;
    auto x = xyz[0];
    auto y = xyz[1];
    auto z = xyz[2];

    points_[i].second[0] =
        x * (cos(phi) + c[0] * c[0] * (1 - cos(phi))) +
        y * (c[0] * c[1] * (1 - cos(phi)) - c[2] * sin(phi)) +
        z * (c[0] * c[2] * (1 - cos(phi)) + c[1] * sin(phi));

    points_[i].second[1] =
        x * (c[1] * c[0] * (1 - cos(phi)) + c[2] * sin(phi)) +
        y * (cos(phi) + c[1] * c[1] * (1 - cos(phi))) +
        z * (c[1] * c[2] * (1 - cos(phi)) - c[0] * sin(phi));

    points_[i].second[2] =
        x * (c[2] * c[0] * (1 - cos(phi)) - c[1] * sin(phi)) +
        y * (c[2] * c[1] * (1 - cos(phi)) + c[0] * sin(phi)) +
        z * (cos(phi) + c[2] * c[2] * (1 - cos(phi)));
  }
}

std::ostream &operator<<(std::ostream &os, const RigidBody &rb) {
  std::cout << "[ ";
  for (const auto &point : rb.points_) {

    std::cout << "(" << std::get<0>(point) << ", {" << std::get<1>(point)[0]
              << ", " << std::get<1>(point)[1] << ", " << std::get<1>(point)[2]
              << "})";
  }
  std::cout << " ]";
  return os;
}
