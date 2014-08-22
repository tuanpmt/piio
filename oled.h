#ifndef _OLED_H_
#define _OLED_H_
#include <node.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>
#define swap(a, b) { int16_t t = a; a = b; b = t; }
class OLED : public node::ObjectWrap {
public:
    
    static void Init(v8::Handle<v8::Object> exports);
    
private:
     explicit OLED();
    ~OLED();
    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> setup(const v8::Arguments& args);
    static v8::Handle<v8::Value> writePixel(const v8::Arguments& args);
    static v8::Handle<v8::Value> fill(const v8::Arguments& args);
    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> gotoxy(const v8::Arguments& args);
    static v8::Handle<v8::Value> text(const v8::Arguments& args);
    static v8::Handle<v8::Value> display(const v8::Arguments& args);

    static void cmd(OLED* obj, uint8_t* data, int length);
    static void data(OLED* obj, uint8_t* data, int length);
    static void gotoxy(OLED* obj, int x, int y);
    static char *strToPtr(v8::Local<v8::Value> value, const char *fallback);
    static void drawPixel(OLED* obj, int x, int y, int color);
    static void display(OLED *obj);
    static void drawLine(OLED *obj, int x0, int y0, int x1, int y1, int color);
    static void drawCircle(OLED *obj, int x0, int y0, int r, int color);
    static void drawChar(OLED *obj, unsigned char c) ;
    static void drawFastHLine(OLED *obj, int x, int y, int w, int color); 
    static void drawFastVLine(OLED *obj, int x, int y, int h, int color); 
    static void drawRect(OLED *obj, int x, int y, int w, int h, int color); 
    static void fillRect(OLED *obj, int x, int y, int w, int h, int color);
    static void write(OLED *obj, char c);
    int pinDc, pinRst, csCh, sizeWidth, sizeHeigh, rotate, textbgcolor, textcolor, cursor_y, cursor_x, textsize, wrap;

};
#endif