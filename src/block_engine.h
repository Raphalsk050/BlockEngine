#pragma once

#include "types.h"
#include "window/glfw_window.h"
#include "window/window.h"
#include "input/input.h"
#include "input/key_codes.h"
#include "input/mouse_codes.h"

#ifdef DEBUG
#include "log/belog.h"
#endif

namespace BEngine {
  class BlockEngine {
  public:
    // TODO: This is only for test proposes, remove this
    BlockEngine() {
      auto window = new glfw_window();
      window->initialize(800, 600);
#ifdef DEBUG
      Belog::Init();
#endif
    }
  };
}
