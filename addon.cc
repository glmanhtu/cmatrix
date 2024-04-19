#include <nan.h>
#include "matrix.h"

void InitAll(v8::Local<v8::Object> exports) {
  Matrix::Init(exports);
}

NODE_MODULE(addon, InitAll)
