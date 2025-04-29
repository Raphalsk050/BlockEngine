#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class window {
public:
  virtual ~window() = default;

  virtual void initialize(int width, int height) = 0;
  virtual void close() = 0;
};
