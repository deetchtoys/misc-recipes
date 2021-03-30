all:	lib run

lib:
	g++ -shared -fPIC -o libhello.so libhello.cc hello.cc
run:
	luajit main.lua
clean:
	rm *.so
