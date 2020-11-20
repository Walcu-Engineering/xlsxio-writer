#include <xlsxio_write.h>
#include "sheet.h"
#include <string>
#include <cstring>
#include <random>

using namespace std;

Napi::Object Sheet::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func =
    DefineClass(env, "Sheet", {
        InstanceMethod("addColumn", &Sheet::addColumn),
        InstanceMethod("addCellString", &Sheet::addCellString),
        InstanceMethod("addCellInt", &Sheet::addCellInt),
        InstanceMethod("addCellFloat", &Sheet::addCellFloat),
        InstanceMethod("addCellDatetime", &Sheet::addCellDatetime),
        InstanceMethod("nextRow", &Sheet::nextRow),
        InstanceMethod("close", &Sheet::close)
      });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("Sheet", func);
  return exports;
}

Sheet::Sheet(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Sheet>(info) {
  Napi::Env env = info.Env();

  int length = info.Length();

  if (length <= 0 || !info[0].IsString()) {
    Napi::TypeError::New(env, "Filename Expected").ThrowAsJavaScriptException();
    return;
  }

  Napi::String value = info[0].As<Napi::String>();

  if ((this->_handle = xlsxiowrite_open(value.Utf8Value().c_str(), "MySheet")) == NULL) {
    Napi::TypeError::New(env, "Error creating file").ThrowAsJavaScriptException();
    return;
  } 
}

Napi::Value Sheet::addColumn(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  int length = info.Length();
  if (length <= 0 || !info[0].IsString()) {
    Napi::TypeError::New(env, "Column name expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::String colname = info[0].As<Napi::String>();
  xlsxiowrite_add_column(this->_handle, colname.Utf8Value().c_str(), 16);
  return env.Null();
}

Napi::Value Sheet::addCellString(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  int length = info.Length();
  if (length <= 0 || !info[0].IsString()) {
    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::String value = info[0].As<Napi::String>();
  xlsxiowrite_add_cell_string(this->_handle, value.Utf8Value().c_str());
  return env.Null();
}

Napi::Value Sheet::addCellInt(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Int expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::Number value = info[0].As<Napi::Number>();
  xlsxiowrite_add_cell_int(this->_handle, (int64_t) value);
  return env.Null();
}
Napi::Value Sheet::addCellFloat(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Float expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::Number value = info[0].As<Napi::Number>();
  xlsxiowrite_add_cell_float(this->_handle, (double) value);
  return env.Null();
}
Napi::Value Sheet::addCellDatetime(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  int length = info.Length();
  if (length <= 0 || !info[0].IsDate()) {
    Napi::TypeError::New(env, "Date expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  Napi::Date value = info[0].As<Napi::Date>();
  xlsxiowrite_add_cell_datetime(this->_handle, (time_t) value.ValueOf());
  return env.Null();
}


Napi::Value Sheet::nextRow(const Napi::CallbackInfo& info){
  xlsxiowrite_next_row(this->_handle);
  return info.Env().Null();
}
Napi::Value Sheet::close(const Napi::CallbackInfo& info){
  xlsxiowrite_close(this->_handle);
  return info.Env().Null();
}
