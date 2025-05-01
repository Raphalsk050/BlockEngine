#include "glfw_window.h"
#include <glad/glad.h>
#include <linmath.h>
#include "../log/belog.h"

namespace BEngine {
  void glfw_window::initialize(int width, int height) {
    if (!glfwInit()) {
      BENGINE_CORE_CRITICAL("GLFW could not initialize!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window_ = glfwCreateWindow(width, height, "BEngine", NULL, NULL);
    if (!window_) {
      BENGINE_CORE_CRITICAL("Window could not initialize!");
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      BENGINE_CORE_CRITICAL("Failed to initialize GLAD");
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    //glfwSwapInterval(1);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader_);

    fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader_);

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader_);
    glAttachShader(program_, fragment_shader_);
    glLinkProgram(program_);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex_shader_, 512, NULL, infoLog);
      BENGINE_CORE_CRITICAL("Vertex Shader compilation failed: {}", infoLog);
    }

    glGetShaderiv(fragment_shader_, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment_shader_, 512, NULL, infoLog);
      BENGINE_CORE_CRITICAL("Fragment Shader compilation failed: {}", infoLog);
    }

    mvp_location_ = glGetUniformLocation(program_, "MVP");
    vpos_location_ = glGetAttribLocation(program_, "vPos");
    vcol_location_ = glGetAttribLocation(program_, "vCol");

    const GLsizei stride = 5 * sizeof(float);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(vpos_location_, 2, GL_FLOAT, GL_FALSE,
                          stride, (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(vcol_location_, 3, GL_FLOAT, GL_FALSE,
                          stride, (void *) (sizeof(float) * 2));

    while (!glfwWindowShouldClose(window_)) {
      int w, h;
      glfwGetFramebufferSize(window_, &w, &h);
      glViewport(0, 0, w, h);

      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      float ratio;
      mat4x4 m, p, mvp;

      glfwGetFramebufferSize(window_, &width, &height);
      ratio = static_cast<float>(width) / static_cast<float>(height);

      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float) glfwGetTime());
      mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      mat4x4_mul(mvp, p, m);

      glBindVertexArray(vao);
      glUseProgram(program_);
      glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window_);
      glfwPollEvents();
    }

    close();
  }

  void glfw_window::close() {
    glfwDestroyWindow(window_);
    glfwTerminate();
  }
}
