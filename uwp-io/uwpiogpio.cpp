#include "uwpiogpio.h"

namespace uwpio {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

Persistent<Function> GPIO::constructor;

GPIO::GPIO() {
    RoInitialize(RO_INIT_MULTITHREADED);
    
	// No pin mapping. Only pin 5 is used in this example.
    _pin = GpioController::GetDefault()->OpenPin(5);
    if (_pin) {
      _pin->SetDriveMode(GpioPinDriveMode::Output);
    }
    else {
      throw 1;
    }
}

GPIO::~GPIO() {
    RoUninitialize();
}

void GPIO::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "GPIO"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "digitalWrite", DigitalWrite);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "GPIO"),
               tpl->GetFunction());
}

void GPIO::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new GPIO(...)`
    double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    GPIO* obj = new GPIO();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `GPIO(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void GPIO::DigitalWrite(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  GPIO* obj = ObjectWrap::Unwrap<GPIO>(args.Holder());
  
  // args[1] (pin) is ignored in this example
  int value = args[0]->IsUndefined() ? 0 : args[1]->NumberValue();
  
  obj->_pin->Write(static_cast<GpioPinValue>(value));

  args.GetReturnValue().Set(Number::New(isolate, value));
}

}  // namespace uwpio