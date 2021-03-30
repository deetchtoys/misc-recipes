hello = require('hello')
ffi = require('ffi')
io.write(ffi.string(hello:World()))
io.write(ffi.string(hello.time))
