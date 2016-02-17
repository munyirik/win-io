// addon.cc
#include <node.h>
#include "uwpiogpio.h"

namespace uwpio {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  GPIO::Init(exports);
}

NODE_MODULE(uwpio, InitAll)

}  // namespace uwpio