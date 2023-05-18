#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ApexCore/ECS/EnCore.h"
#include "ApexCore/Globals.h"
#include "ApexCore/LogCore.h"

#include <memory>
#include <vector>

namespace ApexCore {
extern std::shared_ptr<Manager> ECS;
extern std::vector<std::shared_ptr<System>> SYSTEMS;

void init();
void begin();

namespace priv {
static GLFWwindow *window;

void update();
void render();

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
} // namespace priv
} // namespace ApexCore
