#include "visualize.h"
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::string xyz_file = "../../data/C29N8H28O4.xyz";
int main() {
  double width = 800;
  double height = 600;
  Molecule molecule(xyz_file);
  sf::RenderWindow window(sf::VideoMode(width, height), "Molecule");

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {

      // Translations if LControl is pressed + l/r/u/d
      case sf::Event::KeyPressed:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
          // Rotations
          // NO z rotations and translations because we're working with
          // XY-projections
          if (event.key.code == sf::Keyboard::Left) {
            molecule.rotateLeft(PI / 12);
          }
          if (event.key.code == sf::Keyboard::Right) {

            molecule.rotateRight(PI / 12);
          }
          if (event.key.code == sf::Keyboard::Up) {
            molecule.rotateUp(PI / 12);
          }
          if (event.key.code == sf::Keyboard::Down) {
            molecule.rotateDown(PI / 12);
          }

        } else {
          // Translations of the model
          if (event.key.code == sf::Keyboard::Left) {
            molecule.moveLeft(1.);
          }

          if (event.key.code == sf::Keyboard::Right) {
            molecule.moveRight(1.);
          }
          if (event.key.code == sf::Keyboard::Up) {
            molecule.moveUp(1.);
          }
          if (event.key.code == sf::Keyboard::Down) {
            molecule.moveDown(1.);
          }
        }
        break;

        // zoom
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
    auto atoms = molecule.getAtoms();
    for (auto &atom : atoms) {
      atom.second.setFillColor(sf::Color(100, 250, 50));
      window.draw(atom.second);
    }

    window.display();
  }
  return 0;
}
