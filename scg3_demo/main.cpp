/**
 * \file main.cpp
 * \brief A simple vascg3 test application.
 *
 * Requires C++11 and OpenGL 3.2 (or later versions).
 *
 * \author Volker Ahlers\n
 *         volker.ahlers@fh-hannover.de
 */

#include <iostream>
#include <stdexcept>
#include "Scg3Demo.h"


/**
 * \brief The main() function.
 */
int main() {
  int result = 0;

  try {
    Scg3Demo scg3Demo;
    scg3Demo.run();
  }
  catch (const std::exception& exc) {
    std::cerr << std::endl << "Exception: " << exc.what() << std::endl;
    result = 1;
  }

  return result;
}
