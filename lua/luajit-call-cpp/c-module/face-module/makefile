all: lib

lib: libFaceManager.cc FaceKernel.cc FaceKernel.h
	g++ -shared -fPIC -o libfacemanagertest.so libFaceManager.cc FaceKernel.cc FaceKernel.h

clean:
	rm *.so
