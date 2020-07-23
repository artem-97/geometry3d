#pragma once

#include "../constants/constants.h"

#include <Eigen/Dense>

Eigen::Vector3d toSph(const Eigen::Vector3d &);

Eigen::Vector3d fromSph(const Eigen::Vector3d &);

Eigen::Vector3d toXYZ(const Eigen::Vector3d &);

Eigen::Vector3d fromXYZ(const Eigen::Vector3d &);
