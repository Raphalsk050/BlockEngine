#pragma once

#include "types.h"
#include "window/glfw_window.h"
#include "window/window.h"

#ifdef DEBUG
#include "log/belog.h"
#endif

namespace BEngine {
  class BlockEngine {
  public:
    BlockEngine() {
      auto window = new glfw_window();
      window->initialize(800, 600);
#ifdef DEBUG
      Belog::Init();
#endif
    }
  };
}
