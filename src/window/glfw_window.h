#pragma once
#include "window.h"

namespace BEngine {
  static const struct {
    float x, y;
    float r, g, b;
  } vertices[3] =
  {
    {-0.6f, -0.4f, 1.f, 0.f, 0.f},
    {0.6f, -0.4f, 0.f, 1.f, 0.f},
    {0.f, 0.6f, 0.f, 0.f, 1.f}
  };

  static const char *vertex_shader_text = R"(
      #version 330 core
      uniform mat4 MVP;
      layout(location = 0) in vec2 vPos;
      layout(location = 1) in vec3 vCol;
      out vec3 color;
      void main()
      {
          gl_Position = MVP * vec4(vPos, 0.0, 1.0);
          color = vCol;
      }
)";


  static const char *fragment_shader_text = R"(
      #version 330 core
      out vec3 color;
      layout(location = 0) out vec4 FragColor;
      void main()
      {
          FragColor = vec4(color,1.0);
      }
      )";


  class glfw_window : public window {
  public:
    glfw_window() = default;

    void initialize(int width, int height) override;

    void close() override;

  private:
    GLFWwindow *window_;
    GLuint vertex_buffer_, vertex_shader_, fragment_shader_, program_;
    GLint mvp_location_, vpos_location_, vcol_location_;
  };
}
