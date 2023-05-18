#pragma once

#include <stdexcept>

#include "ApexCore/Globals.h"

namespace ApexCore {
class Exception : public std::exception {
public:
  Exception(const char *msg) : msg(msg) {}
  virtual const char *what() const throw() {
    LOG.error(msg);
    return msg;
  }

private:
  const char *msg;
};
} // namespace ApexCore
