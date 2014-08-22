#ifndef _GPIO_H_
#define _GPIO_H_
#include <node.h>
#include <stdio.h>
 
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>
 
#define     MODE_OUTPUT         0
#define     MODE_INPUT_FLOAT    1
#define     MODE_INPUT_PULLUP   2
#define     MODE_INPUT_PULLDOWN 3
#define     MODE_INT_RISING     4
#define     MODE_INT_FALLING    5
#define     LEVEL_HIGH           1
#define     LEVEL_LOW            0

class GPIO : public node::ObjectWrap {
public:
    static void Init(v8::Handle<v8::Object> exports);
private:
     explicit GPIO();
    ~GPIO();
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> setup(const v8::Arguments& args);
    static void setupPin(int pin, int model);
    static v8::Handle<v8::Value> read(const v8::Arguments& args);
    static v8::Handle<v8::Value> write(const v8::Arguments& args);

};
#endif