#include <napi.h>
#include "sheet.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return Sheet::Init(env, exports);
}

NODE_API_MODULE(xlsxio, InitAll)
