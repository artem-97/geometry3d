#include "../../src/constants/constants.h"
#include "../../src/point/coordinates.h"
#include "../../src/point/point3d.h"
#include "../../src/point/point3dxyz.h"
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <iostream>

class Point3dTest : public ::testing::Test {};

TEST_F(Point3dTest, Constructors) {

  Point3d p1 = Point3d(1., 2., 3.);
  // Point3d p2 = Eigen::Vector3d(1., 2., 3.);
  Point3d p2(Eigen::Vector3d(1., 2., 3.));
  ASSERT_EQ(p1, p2);

  Point3d p3 = Point3d(p1);
  ASSERT_EQ(p3, p1);
  ASSERT_EQ(p3, p2);

  Point3d p4 = p1;
  ASSERT_EQ(p4, p1);
  ASSERT_EQ(p4, p2);
  ASSERT_EQ(p4, p3);
}

TEST_F(Point3dTest, Getters) {
  double x1(-3.), y1(0.), z1(31234.);
  Point3d p1 = Point3d(x1, y1, z1);

  ASSERT_EQ(p1.getX1(), x1);
  ASSERT_EQ(p1.getX2(), y1);
  ASSERT_EQ(p1.getX3(), z1);
  ASSERT_EQ(p1.getCoordSystem(), CoordSystem::XYZ);
  ASSERT_EQ(p1.getVector(), Eigen::Vector3d(x1, y1, z1));
}

TEST_F(Point3dTest, Setters) {
  double x1(-3.), y1(0), z1(31234.);
  Point3d p1 = Point3d(x1, y1, z1);

  p1.setX1(x1);
  p1.setX2(y1);
  p1.setX3(z1);

  ASSERT_EQ(p1.getX1(), x1);
  ASSERT_EQ(p1.getX2(), y1);
  ASSERT_EQ(p1.getX3(), z1);

  Point3d p2 = Point3d(0, 0, 0);
  p2.setVector(Eigen::Vector3d(x1, y1, z1));
  ASSERT_EQ(p2.getVector(), Eigen::Vector3d(x1, y1, z1));
  ASSERT_EQ(p2, p1);

  p1.setCoordSystem(CoordSystem::SPH);
  ASSERT_EQ(p1.getCoordSystem(), CoordSystem::SPH);
}

TEST_F(Point3dTest, AffineGeometry) {
  double x1(-3.), y1(0.), z1(31234.);
  Point3d p1 = Point3d(x1, y1, z1);
  Point3d p2 = p1;

  p2.T(Eigen::Vector3d(0, 0, 0));
  ASSERT_EQ(p1, p2);

  auto p3 = translate(p2, Eigen::Vector3d(0, 0, 0));
  ASSERT_EQ(p3, p1);
  ASSERT_EQ(p3, p2);

  p3 += {0, 0, 0};
  ASSERT_EQ(p3, p2);

  p3 -= {0, 0, 0};
  ASSERT_EQ(p3, p2);

  auto p4 = translate(p2, Eigen::Vector3d(-132, 3, 12));
  p1.T({-132, 3, 12});
  ASSERT_EQ(p4, p1);

  Eigen::Vector3d v(-1, 345, -221);
  auto p5(p1);
  p5 += v;
  p5 -= v;

  ASSERT_EQ(p5, p1);
}

TEST_F(Point3dTest, Access) {
  double x1(-3.), y1(0), z1(31234.);
  Point3d p1 = Point3d(x1, y1, z1);

  ASSERT_EQ(p1[0], x1);
  ASSERT_EQ(p1[1], y1);
  ASSERT_EQ(p1[2], z1);

  const Point3d p2 = Point3d(x1, y1, z1);

  ASSERT_EQ(p2[0], x1);
  ASSERT_EQ(p2[1], y1);
  ASSERT_EQ(p2[2], z1);
}

class CoordinatesTest : public ::testing::Test {};

TEST_F(CoordinatesTest, Converts) {
  double x1(-3.), y1(10.), z1(31234.);
  using v3d = Eigen::Vector3d;
  v3d v1(x1, y1, z1);
  v3d v2(v1);

  ASSERT_EQ(v1, v1);
  ASSERT_EQ(toXYZ(toSph(v1)), v1);
  ASSERT_EQ(toXYZ(toSph(v1)), v2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
