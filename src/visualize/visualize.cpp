#include "visualize.h"

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <utility>
#include <vector>

// Constructors
Molecule::Molecule(const RigidBody &rb) : RigidBody(rb) {}

void Molecule::draw() {
  double Rx = width / 2;
  double Ry = height / 2;
  for (size_t i = 0; i < points_.size(); i++) {
    double x = points_[i].second.getX1();
    double y = points_[i].second.getX2();
    x += Rx;
    y += Ry;
    sf::CircleShape atom(2.f);
    atom.setPosition(x * scale_factor, y * scale_factor);
  }
}
