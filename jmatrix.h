#ifndef MATRIX_H
#define MATRIX_H

#include <nan.h>
#include "SimpleMatrix.h"

class JMatrix : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit JMatrix(double value = 0);
  explicit JMatrix(int rows, int cols, double initValue = 0);
  ~JMatrix();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void SetCell(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Mds(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  double value_;
  smat::Matrix<double> *data_;
};

#endif
