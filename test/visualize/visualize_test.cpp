#include "../../src/constants/constants.h"
#include "../../src/point/point3d.h"
#include "../../src/rigidbody/rigidbody.h"
#include "../../src/visualize/visualize.h"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include <vector>

using RbPoints = std::vector<std::pair<size_t, Point3d>>;
using MolPoints = std::vector<std::pair<size_t, sf::CircleShape>>;

class MoleculeTest : public ::testing::Test {};

TEST_F(MoleculeTest, Constructors) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  RbPoints points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb(points);
  Molecule mol(rb);
  // std::cout << mol << '\n';
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
