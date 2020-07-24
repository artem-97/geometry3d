#include "../../src/constants/constants.h"
#include "../../src/point/point3d.h"
#include "../../src/rigidbody/rigidbody.h"
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include <vector>

using Points = std::vector<std::pair<size_t, Point3d>>;

class RigidBodyTest : public ::testing::Test {};

TEST_F(RigidBodyTest, Constructors) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  Points points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb1({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}});
  RigidBody rb2(points);
  // RigidBody rb2(rb1);

  ASSERT_NE(rb1, rb2);

  decltype(rb2) rb3 = rb1;
  ASSERT_EQ(rb1, rb3);
}

TEST_F(RigidBodyTest, GettersSetters) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  Points points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb1({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}, {23, {1, 2, 3}}});
  RigidBody rb2(points);
  // RigidBody rb2(rb1);

  ASSERT_NE(rb1, rb2);
  ASSERT_EQ(rb2.getPoints(), points);

  rb2.setPoints({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}, {23, {1, 2, 3}}});
  ASSERT_EQ(rb1, rb2);
}

TEST_F(RigidBodyTest, Translations) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  Points points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb1({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}, {23, {1, 2, 3}}});
  RigidBody rb2(rb1);

  rb1.moveX(-1.2);
  ASSERT_NE(rb1, rb2);

  rb1.moveX(1.2);
  // ASSERT_EQ(rb1, rb2);

  rb1.moveY(-1.2);
  ASSERT_NE(rb1, rb2);

  rb1.moveY(1.2);
  // ASSERT_EQ(rb1, rb2);

  rb1.moveZ(-1.2);
  ASSERT_NE(rb1, rb2);

  rb1.moveZ(1.2);
  // ASSERT_EQ(rb1, rb2);

  rb1.moveTo({0., -2.2, 1.3});
  ASSERT_NE(rb1, rb2);

  rb1.moveTo({0., 2.2, -1.3});
  // ASSERT_EQ(rb1, rb2);
}

TEST_F(RigidBodyTest, Rotations) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  Points points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb1({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}, {23, {1, 2, 3}}});
  RigidBody rb2(rb1);

  rb1.rotateX(PI);
  ASSERT_NE(rb1, rb2);

  rb1.rotateY(PI);
  ASSERT_NE(rb1, rb2);

  rb1.rotateZ(PI);
  ASSERT_NE(rb1, rb2);

  rb1.rotateR({1., 3., -2}, PI);
  ASSERT_NE(rb1, rb2);
}

TEST_F(RigidBodyTest, Utility) {

  Point3d p1 = Point3d(1., 2., 3.);
  Point3d p2 = Point3d(32., 234., 13.);
  Point3d p3 = Point3d(-1., 0., 33.);

  Points points{{1, p1}, {3, p2}, {43, p3}};
  RigidBody rb1({{1, {0.3, 0.1, 3}}, {2, {2, 3, 0.4}}, {23, {1, 2, 3}}});
  RigidBody rb2(points);
  RigidBody rb3(points);

  swap(rb1, rb2);
  ASSERT_NE(rb2, rb3);

  swap(rb1, rb2);
  ASSERT_EQ(rb2, rb3);

  rb1.swap(rb2);
  ASSERT_NE(rb3, rb2);

  rb2.swap(rb1);
  ASSERT_EQ(rb3, rb2);

  RigidBody rb4({{2, {-0.3, 0.1, -3}}, {2, {0.3, -0.1, 3}}, {0, {1, 2, 3}}});
  ASSERT_EQ(rb4.getCenterOfMass(), Eigen::Vector3d(0, 0, 0));

  rb4.toCOMRef();
  decltype(rb4) rb5(rb4);
  rb4.toCOMRef();
  ASSERT_EQ(rb4, rb5);
  rb4.toCOMRef();
  ASSERT_EQ(rb4, rb5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
