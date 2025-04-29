#include "glfw_window.h"

#include "../log/belog.h"

void glfw_window::initialize(int width, int height) {
  if (!glfwInit()) {
    BELOG_CORE_CRITICAL("GLFW could not initialize!");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  window_ = glfwCreateWindow(width, height, "BEngine", NULL, NULL);
  if (!window_) {
    BELOG_CORE_CRITICAL("Window could not initialize!");
  }

  glfwMakeContextCurrent(window_);

  while (!glfwWindowShouldClose(window_))
  {
    glfwGetFramebufferSize(window_, &width, &height);
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }

  close();
}

void glfw_window::close() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}
