#include "src/block_engine.h"

int main() {
  auto *engine = new BEngine::BlockEngine();
  BELOG_CORE_INFO("test");
  return 0;
}
