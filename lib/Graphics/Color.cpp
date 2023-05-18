#include "ApexCore/Graphics/Color.h"

#include <iomanip>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace ApexCore {
Color::Color() {}

Color::Color(std::string hex) : hex(hex) {
  // Validate Hex
  const std::regex hexPattern("^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{8})$");
  if (!std::regex_match(hex, hexPattern)) {
    std::string error = "HEX invalid ";
    error += hex;
    error += "\n";

    throw std::invalid_argument(error.c_str());
  }
  // Set other color codes
  int *rgba = HEX_RGBA(hex.c_str());

  r = rgba[0];
  g = rgba[1];
  b = rgba[2];
  a = rgba[3];

  glR = rgba[0] / 255.0f;
  glG = rgba[1] / 255.0f;
  glB = rgba[2] / 255.0f;
  glA = rgba[3] / 255.0f;

  delete rgba;
}

Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {
  if (r > 255 || g > 255 || b > 255 || a > 255 || r < 0 || g < 0 || b < 0 || a < 0) {
    std::string error = "Color is out of range[0, 255]: (";
    error += r;
    error += ',';
    error += g;
    error += ',';
    error += b;
    error += ',';
    error += a;
    error += ")\n";

    throw std::out_of_range(error.c_str());
  }

  // Set other color codes
  glR = r / 255.0f;
  glG = g / 255.0f;
  glB = b / 255.0f;
  glA = a / 255.0f;

  hex = RGBA_HEX(r, g, b, a);
}

Color::Color(float glR, float glG, float glB, float glA) : glR(glR), glG(glG), glB(glB), glA(glA) {
  if (glR > 1.0 || glG > 1.0 || glB > 1.0 || glA > 1.0 || glR < 0.0 || glG < 0.0 || glB < 0.0 || glA < 0.0) {
    std::string error = "Color is out of range[0.0, 1.0]: (";
    error += glR;
    error += ',';
    error += glG;
    error += ',';
    error += glB;
    error += ',';
    error += glA;
    error += ")\n";

    throw std::out_of_range(error.c_str());
  }

  // Set other color codes
  r = glR * 255;
  g = glG * 255;
  b = glB * 255;
  a = glA * 255;

  hex = RGBA_HEX(r, g, b, a);
}

int *Color::HEX_RGBA(const char *hex) {
  std::string code = hex;

  code.erase(0, 1);

  int r = std::stoi(code.substr(0, 2), nullptr, 16);
  int g = std::stoi(code.substr(2, 2), nullptr, 16);
  int b = std::stoi(code.substr(4, 2), nullptr, 16);
  int a;

  try {
    a = std::stoi(code.substr(6, 2), nullptr, 16);
  } catch (std::invalid_argument e) {
    a = 255;
  }

  int *rgba = new int[4];
  rgba[0] = static_cast<int>(r);
  rgba[1] = static_cast<int>(g);
  rgba[2] = static_cast<int>(b);
  rgba[3] = static_cast<int>(a);

  return rgba;
}

std::string Color::RGBA_HEX(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
  int color = (r << 24) | (g << 16) | (b << 8) | a;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(8) << std::hex << color;
  std::string hexCode = "#" + ss.str();

  return hexCode;
}
} // namespace ApexCore
