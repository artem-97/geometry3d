#pragma once

#include "../constants/constants.h"
#include "../point/point3d.h"
#include <Eigen/Dense>
#include <compare>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

class RigidBody {
public:
  using Point = std::pair<size_t, Point3d>;
  using Points = std::vector<Point>;

  // Constructors
  RigidBody(const Points &);
  RigidBody(const RigidBody &);

  // Operator=
  RigidBody &operator=(RigidBody);

  // Getters
  Points getPoints() const;

  // Setters
  void setPoints(Points);

  // Translations in Cartesian coords
  void moveX(double);
  void moveY(double);
  void moveZ(double);
  void moveTo(Point3d);

  // Rotations in Cartesian coords
  void rotateX(double);
  void rotateY(double);
  void rotateZ(double);
  void rotateR(Eigen::Vector3d, double);

  auto operator<=>(const RigidBody &) const = default;
  // Center of Mass Ref.
  Eigen::Vector3d getCenterOfMass() const;
  void toCOMRef();
  friend std::ostream &operator<<(std::ostream &, const RigidBody &);

  // Utilitty
  void swap(RigidBody &);
  friend void swap(RigidBody &, RigidBody &);
  friend void ROTATION_ASSERT(const RigidBody &, const RigidBody &);

private:
  Points points_;
};
