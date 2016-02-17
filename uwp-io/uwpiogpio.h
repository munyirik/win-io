#ifndef UWPIOGPIO_H
#define UWPIOGPIO_H

#include <node.h>
#include <node_object_wrap.h>
#include <roapi.h>

namespace uwpio {

using namespace Platform;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::SerialCommunication;
using namespace Windows::Foundation;
using namespace Windows::Devices::Gpio;

class GPIO : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit GPIO();
  ~GPIO();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void DigitalWrite(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  GpioPin^ _pin;
};

}  // namespace uwpio

#endif