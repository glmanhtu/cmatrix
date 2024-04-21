#ifndef JMATRIX_H
#define JMATRIX_H

#include <nan.h>
#include "SimpleMatrix.h"

class JMatrix : public Nan::ObjectWrap {
 public:
  static NAN_MODULE_INIT(Init);
 private:
  explicit JMatrix(int rows, int cols, double initValue = 0);
  ~JMatrix();

  static NAN_METHOD(New);
  static NAN_METHOD(SetCell);
  static NAN_METHOD(Mds);
  static Nan::Persistent<v8::Function> constructor;
  smat::Matrix<double> *data_;
};

#endif
