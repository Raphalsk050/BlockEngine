#pragma once

#include "types.h"
#include "window/window.h"

#ifdef DEBUG
#include "log/belog.h"
#endif

namespace BEngine {
  class BlockEngine {
  public:
    BlockEngine() {
#ifdef DEBUG
      Belog::Init();
#endif
    }
  };
}
