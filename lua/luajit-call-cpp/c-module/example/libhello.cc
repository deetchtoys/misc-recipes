#include "hello.h"

extern "C" {
    Hello* Hello_new(){
        return new Hello;
    }
    const char* Hello_World(Hello* self){
        return self->World();
    }
    void Hello_gc(Hello* self) {
        delete self;
    }
}
