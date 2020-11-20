#ifndef SHEET_H
#define SHEET_H

#include <xlsxio_write.h>
#include <napi.h>

class Sheet : public Napi::ObjectWrap<Sheet> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Sheet(const Napi::CallbackInfo& info);

 private:
  Napi::Value addColumn(const Napi::CallbackInfo& info);
  Napi::Value addCellString(const Napi::CallbackInfo& info);
  Napi::Value addCellInt(const Napi::CallbackInfo& info);
  Napi::Value addCellFloat(const Napi::CallbackInfo& info);
  Napi::Value addCellDatetime(const Napi::CallbackInfo& info);
  Napi::Value nextRow(const Napi::CallbackInfo& info);
  Napi::Value close(const Napi::CallbackInfo& info);

  xlsxiowriter _handle;
};

#endif
