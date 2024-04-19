#include "matrix.h"

Nan::Persistent<v8::Function> Matrix::constructor;

Matrix::Matrix(double value) : value_(value) {}

Matrix::~Matrix() {}

void Matrix::Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context =
      exports->GetCreationContext().ToLocalChecked();
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Matrix").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "value", GetValue);
  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);
  Nan::SetPrototypeMethod(tpl, "multiply", Multiply);

  constructor.Reset(tpl->GetFunction(context).ToLocalChecked());
  exports->Set(context,
               Nan::New("Matrix").ToLocalChecked(),
               tpl->GetFunction(context).ToLocalChecked());
}

void Matrix::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Matrix(...)`
    double value =
        info[0]->IsUndefined() ? 0 : info[0]->NumberValue(context).FromJust();
    Matrix* obj = new Matrix(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Matrix(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(
        cons->NewInstance(context, argc, argv).ToLocalChecked());
  }
}

void Matrix::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Matrix* obj = ObjectWrap::Unwrap<Matrix>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void Matrix::PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Matrix* obj = ObjectWrap::Unwrap<Matrix>(info.Holder());
  obj->value_ += 1;
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void Matrix::Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
  Matrix* obj = ObjectWrap::Unwrap<Matrix>(info.Holder());
  double multiple =
      info[0]->IsUndefined() ? 1 : info[0]->NumberValue(context).FromJust();

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);

  const int argc = 1;
  v8::Local<v8::Value> argv[argc] = {Nan::New(obj->value_ * multiple)};

  info.GetReturnValue().Set(
      cons->NewInstance(context, argc, argv).ToLocalChecked());
}