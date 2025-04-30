#pragma once
#include "window.h"

namespace BEngine {
  class glfw_window : public window{
  public:
    glfw_window() = default;

    void initialize(int width, int height) override;

    void close() override;
  private:
    GLFWwindow* window_;
  };
}
