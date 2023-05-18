#include "ApexCore/ApexCore.h"
#include "ApexCore/Utils/Except.h"

#include <filesystem>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <sstream>
#include <string>
#include <thread>

namespace ApexCore {

std::shared_ptr<Manager> ECS;
std::vector<std::shared_ptr<System>> SYSTEMS;

void init() {
  // Initialize logger
  LOG.log("Initializing ApexCore");

  // If ApexCore dir doesn't exist, then make it
  if (!std::filesystem::exists("ApexCore")) {
    std::filesystem::create_directory("ApexCore");
    LOG.log("Created ApexCore/");
  }
  // grab application.json data
  if (!std::filesystem::exists("ApexCore/application.json")) {
    std::fstream application_json_write("ApexCore/application.json", std::ios_base::out);
    application_json_write << "{\"width\" : 800,\n\"height\" : 600,\n\"title\": \"default\"}";
    LOG.log("Created ApexCore/application.json");
  }

  std::fstream application_json("ApexCore/application.json", std::ios_base::in);
  rapidjson::IStreamWrapper json(application_json);

  rapidjson::Document application_json_doc;
  application_json_doc.ParseStream(json);

  if (!application_json_doc.IsObject())
    throw Exception("Application.json is not an object");
  // Get width
  if (!application_json_doc.HasMember("width"))
    throw Exception("Application.json does not contain \"width\"");
  if (!application_json_doc["width"].IsInt())
    throw Exception("Application.json[\"width\"] is not an int");
  WINDOW.WIDTH = application_json_doc["width"].GetInt();
  // Get height
  if (!application_json_doc.HasMember("height"))
    throw Exception("Application.json does not contain \"height\"");
  if (!application_json_doc["height"].IsInt())
    throw Exception("Application.json[\"height\"] is not an int");
  WINDOW.HEIGHT = application_json_doc["height"].GetInt();
  // Get title
  if (!application_json_doc.HasMember("title"))
    throw Exception("Application.json does not contain \"title\"");
  if (!application_json_doc["title"].IsString())
    throw Exception("Application.json[\"title\"] is not a string");
  WINDOW.TITLE = application_json_doc["title"].GetString();

  // get optional application.json values;
  if (application_json_doc.HasMember("fps")) {
    if (!application_json_doc["fps"].IsInt())
      throw Exception("Application.json[\"fps\"] is not an int");
    WINDOW.FPS = application_json_doc["fps"].GetInt();
  } else {
    LOG.warning("Application.json doesn't include \"fps\", defaulting to 60");
    WINDOW.FPS = 60;
  }
  if (application_json_doc.HasMember("color")) {
    if (!application_json_doc["color"].IsString())
      throw Exception("Application.json[\"color\"] is not a string");
    WINDOW.COLOR = Color(application_json_doc["color"].GetString());
  } else {
    LOG.warning("Application.json doesn't include \"color\", defaulting to #33B1D9");
    WINDOW.COLOR = Color("#33B1D9");
  }

  // Set default values
  MOUSE.X = 0;
  MOUSE.Y = 0;

  ECS = std::make_shared<ApexCore::Manager>();

  // Inialize GLFW
  LOG.log("Initializing GLFW");

  if (!glfwInit())
    throw Exception("GLFW has failed to initialize");

  // Window Hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  priv::window = glfwCreateWindow(WINDOW.WIDTH, WINDOW.HEIGHT, WINDOW.TITLE, NULL, NULL);

  if (!priv::window) {
    glfwTerminate();
    throw Exception("GLFWwindow failed to be created");
  }

  // Window Callbacks
  glfwSetKeyCallback(priv::window, priv::keyCallback);
  glfwSetCursorPosCallback(priv::window, priv::cursorPositionCallback);
  glfwSetMouseButtonCallback(priv::window, priv::mouseButtonCallback);
  glfwSetFramebufferSizeCallback(priv::window, priv::framebufferSizeCallback);

  glfwMakeContextCurrent(priv::window);
  LOG.log("GLFW Initialized");
  LOG.log("Initializing GLAD");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw Exception("GLAD failed to initialize");
  }

  LOG.log("GLAD Initialized");

  LOG.log("ApexCore Initialized");
}

void begin() {
  glViewport(0, 0, WINDOW.WIDTH, WINDOW.HEIGHT);

  double last_time = glfwGetTime();
  WINDOW.DELTA_TIME = 0.0;
  const double frame_time = 1.0 / WINDOW.FPS;

  while (!glfwWindowShouldClose(priv::window)) {
    double current_time = glfwGetTime();

    WINDOW.DELTA_TIME = current_time - last_time;
    last_time = current_time;

    double sleep_time = frame_time - WINDOW.DELTA_TIME;

    if (sleep_time > 0.0)
      std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));

    priv::update();
    priv::render();

    glfwSwapBuffers(priv::window);
    glfwPollEvents();
  }
  LOG.log("Window was closed");
  glfwTerminate();
}

void priv::update() {
  for (std::shared_ptr<System> system : ApexCore::SYSTEMS) {
    system->update(ECS);
  }
}
void priv::render() {
  glClearColor(WINDOW.COLOR.glR, WINDOW.COLOR.glG, WINDOW.COLOR.glB, WINDOW.COLOR.glA);
  glClear(GL_COLOR_BUFFER_BIT);
}

void priv::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {}

void priv::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
  MOUSE.X = xpos;
  MOUSE.Y = ypos;
}

void priv::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {}

void priv::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  WINDOW.WIDTH = width;
  WINDOW.HEIGHT = height;
  glViewport(0, 0, width, height);
}
} // namespace ApexCore
