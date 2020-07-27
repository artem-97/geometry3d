#include "../constants/constants.h"
#include "../rigidbody/rigidbody.h"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

class Molecule : public RigidBody {
public:
  using Point = std::pair<size_t, Point3d>;
  using Points = std::vector<Point>;
  // Constructors
  Molecule(const RigidBody &);

  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();

  void draw();

  // Utility

private:
  double scale_factor = 30;
  double translation_step = 10;
  double rotational_step = PI / 12;

  double width = 800;
  double height = 600;
};
