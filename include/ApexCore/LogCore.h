#pragma once

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

namespace ApexCore {
enum LOG_LEVEL { DEBUG, WARNING, ERROR };

class Logger {
public:
  Logger(std::string name) : name(name) {
    // Validate name input
    if (!name_is_valid(name))
      throw std::invalid_argument("Characters in name are invalid");

    // Create log directory if it doesnt exist
    std::string dir = "logs/" + name;
    if (!std::filesystem::exists(dir)) {
      std::filesystem::create_directories(dir);
    }

    // Create log file according to the time
    log_file.open(dir + "/" + get_current_time() + ".log", std::ios_base::out);
  }

  ~Logger() { log_file.close(); }

  void warning(std::string msg) { log(msg, LOG_LEVEL::WARNING); }

  void debug(std::string msg) { log(msg); }
  void error(std::string msg) { log(msg, LOG_LEVEL::ERROR); }

  void log(std::string msg, LOG_LEVEL level = LOG_LEVEL::DEBUG) {
    std::string cout;
    std::string fout;
    switch (level) {
    case LOG_LEVEL::DEBUG:
      cout = "DEBUG";
      fout = "DEBUG";
      break;
    case LOG_LEVEL::WARNING:
      cout = "\033[38;5;166mWARNING\033[0m";
      fout = "WARNING";
      break;
    case LOG_LEVEL::ERROR:
      cout = "\033[38;5;160mERROR\033[0m";
      fout = "ERROR";
      break;
    }

    std::string c_output = "" + get_current_time() + " [" + cout + "] " + msg + "\n";
    std::string f_output = "" + get_current_time() + " [" + fout + "] " + msg + "\n";
    printf(c_output.c_str());
    log_file << f_output;
    log_file.flush();
  }

private:
  std::string name;
  std::fstream log_file;

  bool name_is_valid(std::string name) {
    // check that each character is allowed
    for (char c : name) {
      int ascii = c;
      // make sure ascii isnt a special exception
      if (ascii != 32 && ascii != 45 && ascii != 95) {
        // check range 48-57
        if (ascii < 48 || (ascii > 57 && ascii < 65))
          return false;
        // check range 65-90
        else if ((ascii > 57 && ascii < 65) || (ascii > 90 && ascii < 97))
          return false;
        // check range 97-122
        else if ((ascii > 90 && ascii < 97) || ascii > 122)
          return false;
      }
    }
    return true;
  }
  std::string get_current_time() {
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output_time = std::ctime(&time);
    output_time.replace(output_time.end() - 1, output_time.end(), "");
    return output_time;
  }
};
} // namespace ApexCore
