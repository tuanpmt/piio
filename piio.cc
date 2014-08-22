#include <node.h>
#include "gpio.h"
#include "spi.h"
#include "oled.h"
#include "bcm2835.h"
using namespace v8;


void InitAll(Handle<Object> exports, Handle<Object> module) {

    bcm2835_init();
    GPIO::Init(exports);
    SPI::Init(exports);
    OLED::Init(exports);
}

NODE_MODULE(piio, InitAll);