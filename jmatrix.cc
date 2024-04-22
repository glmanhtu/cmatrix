#include "jmatrix.h"

Nan::Persistent<v8::Function> JMatrix::constructor;

JMatrix::JMatrix(int rows, int cols, double initValue) {
  this->data_ = new smat::Matrix<double>(rows, cols, initValue);
}

JMatrix::~JMatrix() {
  if (this->data_ != NULL) {
    delete this->data_;
  }
}

NAN_MODULE_INIT(JMatrix::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("JMatrix").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "setCell", SetCell);
  Nan::SetPrototypeMethod(tpl, "mds", Mds);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("JMatrix").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(JMatrix::New) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
  if (!info.IsConstructCall()) {
    return Nan::ThrowError(Nan::New("JMatrix::New - called without new keyword").ToLocalChecked());
  }

   // expect exactly 3 arguments
  if (info.Length() != 3) {
    return Nan::ThrowError(Nan::New("JMatrix::New - expected arguments rows, cols, defaultValue").ToLocalChecked());
  }

  // expect arguments to be numbers
  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    return Nan::ThrowError(Nan::New("JMatrix::New - expected arguments to be numbers").ToLocalChecked());
  }

  JMatrix* obj = new JMatrix(
    info[0]->NumberValue(context).FromJust(), 
    info[1]->NumberValue(context).FromJust(), 
    info[2]->NumberValue(context).FromJust()
  );
  
  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}


NAN_METHOD(JMatrix::Mds) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
  JMatrix* obj = ObjectWrap::Unwrap<JMatrix>(info.Holder());
  
  // expect exactly 2 arguments
  if (info.Length() != 3) {
    return Nan::ThrowError(Nan::New("JMatrix::Mds - expected arguments dim, iters, seed").ToLocalChecked());
  }

  // expect arguments to be numbers
  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    return Nan::ThrowError(Nan::New("JMatrix::Mds - expected arguments to be numbers").ToLocalChecked());
  }

  int dim = info[0]->NumberValue(context).FromJust();                                                      // number of dimensions
  int iter = info[1]->NumberValue(context).FromJust();                                                     // number of iterations
  int seed = info[2]->NumberValue(context).FromJust();                                                    
    
  smat::Matrix<double> *mdsRes = smat::MDS_SMACOF(obj->data_, NULL, dim, iter, seed);

  v8::Local<v8::Array> result = Nan::New<v8::Array>(mdsRes->columns());
  for (int i = 0; i < mdsRes->columns(); i++) {
    v8::Local<v8::Array> column = Nan::New<v8::Array>(mdsRes->rows());
    for (int j = 0; j < mdsRes->rows(); j++) {
      Nan::Set(column, j, Nan::New(mdsRes->get(j, i)));
    }
    Nan::Set(result, i, column);
  }
  
  info.GetReturnValue().Set(result);
}

NAN_METHOD(JMatrix::SetCell) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
  JMatrix* obj = ObjectWrap::Unwrap<JMatrix>(info.Holder());
  int row = info[0]->NumberValue(context).FromJust();
  int col = info[1]->NumberValue(context).FromJust();
  double value = info[2]->NumberValue(context).FromJust();

  if (row >= obj->data_->rows()) {
    return Nan::ThrowError(Nan::New("JMatrix::SetCell - row is higher than total rows").ToLocalChecked());
  }
  if (col >= obj->data_->columns()) {
    return Nan::ThrowError(Nan::New("JMatrix::SetCell - col is higher than total cols").ToLocalChecked());
  }

  obj->data_->set(row, col, value);
  info.GetReturnValue().Set(Nan::New(obj->data_->get(row, col)));
}