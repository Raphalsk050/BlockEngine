#pragma once
#include "window.h"


class glfw_window : public window{
public:
  void initialize(int width, int height) override;

  void close() override;
  private:
  GLFWwindow* window_;
};
