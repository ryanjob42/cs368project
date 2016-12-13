// This is a change that does nothing

#include "Matrix.hpp"

#include <ostream>

int main() {
  // Bad creation
  try {
    Matrix<int> fucked(-1, 0);
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Matrix<int> fucked(-1, 1);
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Matrix<int> fucked(1, 0);
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  Matrix<int> m1(2, 2);
  Matrix<int> m2(3, 3);
  Matrix<int> m3(3, 5);
  Matrix<int> m4(3, 3);

  // Bad operations
  try {
    std::cout << m1 + m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1 - m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1 * m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1[69][0] << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1[m1.getRows()][0] << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1[-69][0] << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  // Good operations
  try {
    std::cout << m4 + m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m4 - m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m3 * m2 << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::cout << m1[0][0] << std::endl;
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}
