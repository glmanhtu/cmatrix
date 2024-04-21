#include <nan.h>
#include "jmatrix.h"

NAN_MODULE_INIT(InitModule) {
  JMatrix::Init(target);
}

NODE_MODULE(cmatrix, InitModule)
