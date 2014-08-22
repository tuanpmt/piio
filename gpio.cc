#include <node.h>
#include "gpio.h"
#include "bcm2835.h"
using namespace v8;

Persistent<Function> GPIO::constructor;

GPIO::GPIO(){

}
GPIO::~GPIO(){
  bcm2835_close();
}
#define DBUS_BUS_SESSION 0
#define DBUS_BUS_SYSTEM 1
void GPIO::Init(Handle<Object> exports){
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("GPIO"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setup"),
        FunctionTemplate::New(setup)->GetFunction());
        
    tpl->PrototypeTemplate()->Set(String::NewSymbol("read"),
        FunctionTemplate::New(read)->GetFunction());
        
    tpl->PrototypeTemplate()->Set(String::NewSymbol("write"),
        FunctionTemplate::New(write)->GetFunction());
        
            
    NODE_DEFINE_CONSTANT(tpl, MODE_OUTPUT);
    NODE_DEFINE_CONSTANT(tpl, MODE_INPUT_FLOAT);
    NODE_DEFINE_CONSTANT(tpl, MODE_INPUT_PULLUP);
    NODE_DEFINE_CONSTANT(tpl, MODE_INPUT_PULLDOWN);
    NODE_DEFINE_CONSTANT(tpl, MODE_INT_RISING);
    NODE_DEFINE_CONSTANT(tpl, MODE_INT_FALLING);
    NODE_DEFINE_CONSTANT(tpl, LEVEL_HIGH);
    NODE_DEFINE_CONSTANT(tpl, LEVEL_LOW);
    

    //tpl->Set("func_property", v8::Number::New(1));
    
    constructor = Persistent<Function>::New(tpl->GetFunction());
    
    exports->Set(String::NewSymbol("GPIO"), constructor);
}

Handle<Value> GPIO::New(const Arguments& args) {
  HandleScope scope;

  if (args.IsConstructCall()) {

    GPIO* obj = new GPIO();

    obj->Wrap(args.This());
    return args.This();
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.

    return scope.Close(constructor->NewInstance());
  }
}
void GPIO::setupPin(int pin, int mode) {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    switch(mode){
        case 0:
            bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
            break;
        case 1:
            bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_OFF);
            break;
        case 2:
            bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
            break;
        case 3:
            bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_DOWN);
            break;  
        case 4:
        case 5:
            /*TODO: not implement yet */
            break;
            
    }
    
    //  with a pullup
    bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
    // And a low detect enable
    bcm2835_gpio_len(pin);
}
Handle<Value> GPIO::setup(const Arguments& args) {
    HandleScope scope;
    GPIO* obj = ObjectWrap::Unwrap<GPIO>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[2]);
    
    const int argc = 1;
    Local<Value> argv[argc] = {String::New("")};
    
    /* Check number of arguments*/
    if (args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if(!args[1]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be number")));
        return scope.Close(Undefined());
    }
    int pinMode = args[1]->IntegerValue();
    
    if(pinMode > 3 && !cb->IsFunction()) {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, arg 3 must be callback for interrupt")));
        return scope.Close(Undefined());
    }
    
    if(args[0]->IsArray()){
        Local<Array> pins = Array::Cast(*args[0]);
        for(int i=0; i<pins->Length(); i++){
            Local<Value> pin = pins->Get(i);
            if(pin->IsNumber()){
                setupPin(pin->IntegerValue(), pinMode);
            }
        }
    } else if(args[0]->IsNumber()){
        setupPin(args[0]->IntegerValue(), pinMode);
    } else {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be number or array")));
        return scope.Close(Undefined());
    }

    if (cb->IsFunction()) {
         // callback not defined, ignore
         cb->Call(Context::GetCurrent()->Global(), argc, argv);
         return scope.Close(Undefined());
    }
    return scope.Close(Undefined());
}
Handle<Value> GPIO::write(const Arguments& args) {
    HandleScope scope;
    GPIO* obj = ObjectWrap::Unwrap<GPIO>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[2]);
    const int argc = 1;
    Local<Value> argv[argc] = {String::New("")};
    
    if (args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if(!args[1]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be number")));
        return scope.Close(Undefined());
    }
    int value = args[1]->IntegerValue();
    
    if(args[0]->IsArray()){
        Local<Array> pins = Array::Cast(*args[0]);
        for(int i=0; i<pins->Length(); i++){
            Local<Value> pin = pins->Get(i);
            bcm2835_gpio_write(pin->IntegerValue(), value);
        }
    } else if(args[0]->IsNumber()){
        bcm2835_gpio_write(args[0]->IntegerValue(), value);
    } else {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be number or array")));
        return scope.Close(Undefined());
    }
    
    return scope.Close(Undefined());
    
}
Handle<Value> GPIO::read(const Arguments& args) {
    HandleScope scope;
    GPIO* obj = ObjectWrap::Unwrap<GPIO>(args.This());
    Local<Function> cb = Local<Function>::Cast(args[1]);
    


    
    if (args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    if (!cb->IsFunction()) {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be callback function")));
        return scope.Close(Undefined());
    }
    if(args[0]->IsArray()){
        
        Local<Array> pins = Array::Cast(*args[0]);
        //Local<Array> array = Local<Array>::New(Uint32::New(pins->Length())); 
        //Handle<Array> array = Array::New(pins->Length());
        
        for(int i=0; i<pins->Length(); i++){
            Local<Value> pin = pins->Get(i);
            //array.Set(i, bcm2835_gpio_lev(pin->IntegerValue()));
        }
        //argv[argc] = {array};
        //cb->Call(Context::GetCurrent()->Global(), argc, argv);
        return scope.Close(Undefined());
    } else if(args[0]->IsNumber()){
        int pin = args[0]->IntegerValue();
        int value = bcm2835_gpio_lev(pin);
        printf("Read pin %d, value: %d\n",pin, value);
        const int argc = 1;
        Local<Value> argv[argc] = {Local<Value>::New(Integer::New(value))};
        cb->Call(Context::GetCurrent()->Global(), argc, argv);
        return scope.Close(Undefined());
    } else {
        ThrowException(Exception::TypeError(String::New("Wrong type of arguments, must be number or array")));
        return scope.Close(Undefined());
    }
         // callback not defined, ignore
    
    
    
    return scope.Close(Undefined());
    
}
