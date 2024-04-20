#include <nan.h>
#include "jmatrix.h"

void InitAll(v8::Local<v8::Object> exports) {
  JMatrix::Init(exports);
}

NODE_MODULE(addon, InitAll)
