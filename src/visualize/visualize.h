#include "../constants/constants.h"
#include "../rigidbody/rigidbody.h"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <vector>

class Molecule : public RigidBody {
public:
  // Constructors
  Molecule(const RigidBody &);
  Molecule(const std::string &);

  // Getter
  std::vector<std::pair<size_t, sf::CircleShape>> getAtoms() const;

  // Translations
  void moveLeft(double);
  void moveRight(double);
  void moveUp(double);
  void moveDown(double);

  // Rotations
  void rotateLeft(double);
  void rotateRight(double);
  void rotateUp(double);
  void rotateDown(double);

  // Utility
  friend std::ostream &operator<<(std::ostream &, const Molecule &);

private:
  double scale_factor = 30;
  double translation_step = 10;
  double rotational_step = PI / 12;

  double width = 800;
  double height = 600;
};
