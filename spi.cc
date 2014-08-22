#include <node.h>
#include "spi.h"
#include "bcm2835.h"
using namespace v8;

Persistent<Function> SPI::constructor;

SPI::SPI(){

}
SPI::~SPI(){
  
}

void SPI::Init(Handle<Object> exports){
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("SPI"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setup"),
        FunctionTemplate::New(setup)->GetFunction());
        
    tpl->PrototypeTemplate()->Set(String::NewSymbol("read"),
        FunctionTemplate::New(read)->GetFunction());
        
    tpl->PrototypeTemplate()->Set(String::NewSymbol("write"),
        FunctionTemplate::New(write)->GetFunction());
        
 
    
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("SPI"), constructor);
    

}

Handle<Value> SPI::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {

    SPI* obj = new SPI();
    
    Local<Function> cb = Local<Function>::Cast(args[0]);

    obj->Wrap(args.This());
    

    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    return scope.Close(constructor->NewInstance(argc, argv));
  }
}
Handle<Value> SPI::setup(const Arguments& args) {
    HandleScope scope;
    SPI* obj = ObjectWrap::Unwrap<SPI>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[2]);
    const int argc = 1;
    Local<Value> argv[argc] = {String::New("")};


    if (cb->IsFunction()) {
         // callback not defined, ignore
         cb->Call(Context::GetCurrent()->Global(), argc, argv);
         return scope.Close(Undefined());
    }
    return scope.Close(Undefined());
}
Handle<Value> SPI::write(const Arguments& args) {
    HandleScope scope;
    SPI* obj = ObjectWrap::Unwrap<SPI>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[2]);
    const int argc = 1;
    Local<Value> argv[argc] = {String::New("")};
    
    
    if (cb->IsFunction()) {
         // callback not defined, ignore
         cb->Call(Context::GetCurrent()->Global(), argc, argv);
         return scope.Close(Undefined());
    }
    return scope.Close(Undefined());
    
}
Handle<Value> SPI::read(const Arguments& args) {
    HandleScope scope;
    SPI* obj = ObjectWrap::Unwrap<SPI>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[1]);
    const int argc = 2;
    int retval = 0;
    Local<Value> argv[argc] = {String::New(""), Number::New(retval)};
     if (cb->IsFunction()) {
         // callback not defined, ignore
         cb->Call(Context::GetCurrent()->Global(), argc, argv);
         return scope.Close(Undefined());
    }
    return scope.Close(Undefined());
    
}
