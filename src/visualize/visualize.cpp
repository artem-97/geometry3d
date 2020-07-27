#include "visualize.h"

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

// Constructors
Molecule::Molecule(const RigidBody &rb) : RigidBody(rb) {}
Molecule::Molecule(const std::string &file_name) : RigidBody(file_name) {}

std::vector<std::pair<size_t, sf::CircleShape>> Molecule::getAtoms() const {
  double Rx = width / 2;
  double Ry = height / 2;

  std::vector<std::pair<size_t, sf::CircleShape>> res(points_.size());
  for (size_t i = 0; i < points_.size(); i++) {
    auto point = points_[i];
    auto v = point.second.getVector();
    sf::CircleShape atom(2.0f);
    atom.setPosition(scale_factor * v[0] + Rx, scale_factor * v[1] + Ry);
    res[i] = {point.first, atom};
  }
  return res;
};

// Translations
/*
void moveLeft(double d) {
  for (size_t i = 0; i < RigidBody::points_.size(); i++) {
    std::pair<size_t, Point3d> &point = points_[i];
    Eigen::Vector3d pos = point.second.getVector();
    pos[0] -= d;
    point.setVector(pos);
  }
}*/

void Molecule::moveLeft(double d) {
  std::for_each(points_.begin(), points_.end(),
                [&](std::pair<size_t, Point3d> &point) {
                  auto pos = point.second.getVector();
                  pos[0] -= d;
                  point.second.setVector(pos);
                });
}

void Molecule::moveRight(double d) {
  std::for_each(points_.begin(), points_.end(),
                [&](std::pair<size_t, Point3d> &point) {
                  auto pos = point.second.getVector();
                  pos[0] += d;
                  point.second.setVector(pos);
                });
}

void Molecule::moveUp(double d) {
  std::for_each(points_.begin(), points_.end(),
                [&](std::pair<size_t, Point3d> &point) {
                  auto pos = point.second.getVector();
                  pos[1] -= d;
                  point.second.setVector(pos);
                });
}

void Molecule::moveDown(double d) {
  std::for_each(points_.begin(), points_.end(),
                [&](std::pair<size_t, Point3d> &point) {
                  auto pos = point.second.getVector();
                  pos[1] += d;
                  point.second.setVector(pos);
                });
}
// Rotations
void Molecule::rotateLeft(double phi) { this->rotateX(phi); }

void Molecule::rotateRight(double phi) { this->rotateX(-phi); }

void Molecule::rotateUp(double phi) { this->rotateY(phi); }

void Molecule::rotateDown(double phi) { this->rotateY(-phi); }

// Utility
std::ostream &operator<<(std::ostream &os, const Molecule &molecule) {
  std::cout << "[ ";
  for (const auto &point : molecule.points_) {

    std::cout << "(" << std::get<0>(point) << ", {" << std::get<1>(point)[0]
              << ", " << std::get<1>(point)[1] << ", " << std::get<1>(point)[2]
              << "})";
  }
  std::cout << " ]";
  return os;
}
