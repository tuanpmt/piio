#ifndef _SPI_H_
#define _SPI_H_
#include <node.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>

#define MODE_0 BCM2835_SPI_MODE0
#define MODE_1 BCM2835_SPI_MODE1
#define MODE_2 BCM2835_SPI_MODE0
#define MODE_3 BCM2835_SPI_MODE1

#define CS_LOW
#define CS_HIGH
#define MSB_FIRST
#define LSB_FIRST

class SPI : public node::ObjectWrap {
public:
    
    static void Init(v8::Handle<v8::Object> exports);
    
private:
     explicit SPI();
    ~SPI();
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> setup(const v8::Arguments& args);
    static v8::Handle<v8::Value> read(const v8::Arguments& args);
    static v8::Handle<v8::Value> write(const v8::Arguments& args);
    
    static v8::Persistent<v8::Function> constructor;

};
#endif