ffi = require('ffi')
ffi.cdef[[
    typedef struct Hello Hello;

    Hello* Hello_new();
    const char* Hello_World(Hello*);
    void Hello_gc(Hello*);
]]
hello = ffi.load('hello')

hello_index = {
    World = hello.Hello_World,
    time = hello.time,
}
hello_mt = ffi.metatype('Hello', {
    __index = hello_index
})
Hello = ffi.gc(hello.Hello_new(), hello.Hello_gc)

return Hello
