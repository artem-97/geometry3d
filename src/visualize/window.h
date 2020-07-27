#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class Window {
public:
  Window(double, double);

private:
  int width_ = 800;
  int height_ = 600;
};

std::string xyz_file = "../data/C29N8H28O4.xyz";

int main() {
  sf::RenderWindow window(sf::VideoMode(width, height), "Molecule");

  MoleculeToDraw molecule(xyz_file);
  MoleculeToDraw molecule2(xyz_file2);

  bool pressedl = false;
  double beginX = 0;
  double beginY = 0;
  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::MouseButtonPressed) {
        if ((event.mouseButton.button == sf::Mouse::Left) && (!pressedl)) {
          pressedl = true;
          double beginX = event.mouseButton.x;
          double beginY = event.mouseButton.y;
        }
      }
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          pressedl = false;
          double endX = event.mouseMove.x;
          double endY = event.mouseMove.y;
          Eigen::Vector3d R(endX - beginX, endY - beginY, 0);
          molecule.RotateModelR(R, R.norm() * PI / 12);
        }
      }
      switch (event.type) {

      // Translations if LControl is pressed + l/r/u/d
      case sf::Event::KeyPressed:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
          // Rotations
          // NO z rotations and translations because we're working with
          // XY-projections
          if (event.key.code == sf::Keyboard::Left) {
            molecule.RotateModelX(PI / 12);
            // molecule.RotateModelX();
            // molecule.update();
          }
          if (event.key.code == sf::Keyboard::Right) {

            molecule.RotateModelX(-PI / 12);
            // molecule.RotateModelY();
            // molecule.update();
          }
          if (event.key.code == sf::Keyboard::Up) {
            molecule.RotateModelY(PI / 12);
            // molecule.RotateY(PI / 12);
            // molecule.update();
          }
          if (event.key.code == sf::Keyboard::Down) {
            molecule.RotateModelY(-PI / 12);
            // molecule.update();
          }

        } else {
          // Translations of the model
          // Real molecule is in the R = 0 (COM ref.frame)
          if (event.key.code == sf::Keyboard::Left) {
            molecule.MoveModelLeft();
            // molecule.movex(-1);
            // molecule.update();
          }

          if (event.key.code == sf::Keyboard::Right) {
            molecule.MoveModelRight();
            // molecule.movex(1);
            // molecule.update();
          }
          if (event.key.code == sf::Keyboard::Up) {
            molecule.MoveModelUp();
            // molecule.movey(-1);
            // molecule.update();
          }
          if (event.key.code == sf::Keyboard::Down) {
            molecule.MoveModelDown();
            // molecule.movey(1);
            // molecule.update();
          }
        }
        break;

      // zoom
      case sf::Event::MouseWheelMoved:
        if (event.mouseWheel.delta > 0) {
          // zoom in +10%
          for (auto &atom : molecule.atoms) {
            atom.setRadius(atom.getRadius() * 1.1f);
          }
        } else {
          // zoom out -10%
          for (auto &atom : molecule.atoms) {
            atom.setRadius(atom.getRadius() * 0.9f);
          }
        }
        break;

      // window closed
      case sf::Event::Closed:
        window.close();
        break;

      // we don't process other types of events
      default:
        break;
      }
    }

    // draw it
    window.clear();
    for (auto &e : molecule.atoms) {
      e.setFillColor(sf::Color(100, 250, 50));
      window.draw(e);
    }

    sf::VertexArray line(sf::Lines, 2);
    auto fst = molecule.symmetry[0].getPosition();
    auto snd = molecule.symmetry[1].getPosition();

    line[0].position = sf::Vector2f(fst.x, fst.y);
    line[1].position = sf::Vector2f(snd.x, snd.y);
    //    auto CM = molecule.CenterOfMassModel();
    //    sf::VertexArray line(sf::Lines, 2); // or sf::LineStrip
    //    line[0].position = sf::Vector2f(CM[0], CM[1]);
    line[0].color = sf::Color(100, 0, 200);
    //   line[1].position =
    //       sf::Vector2f(molecule.symmetry_axis[0], molecule.symmetry_axis[1]);
    line[1].color = sf::Color(400, 400, 200);

    window.draw(line);
    // molecule.Inertia();
    // std::cout << '\n' << COM << '\n';

    //    auto COM = molecule.CenterOfMass();
    //  std::cout << "dddddddd" << COM << '\n';
    // sf::CircleShape C((COM[0] * 30, COM[1] * 30), 3);
    // window.draw(C);
    window.display();
  }
  return 0;
}
