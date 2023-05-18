/**
 * @file Color.h
 * @brief Contains Color class
 *
 * This file contains the Color class for ApexCore
 *
 *
 * @data 2023-04-25
 */

#pragma once

#include <string>

namespace ApexCore {

class Color {
public:
  std::string hex;
  unsigned int r, g, b, a;
  float glR, glG, glB, glA;

  Color();

  Color(std::string hex);
  Color(int r, int g, int b, int a = 255);
  Color(float glR, float glG, float glB, float glA = 1.0f);

private:
  int *HEX_RGBA(const char *hex);

  std::string RGBA_HEX(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
};
} // namespace ApexCore
