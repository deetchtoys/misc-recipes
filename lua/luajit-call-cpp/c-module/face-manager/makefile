all: lib-lua

lib-face-kernel: FaceKernel.cc FaceKernel.h
	g++ -shared -fPIC -o libfacekerneltest.so FaceKernel.cc FaceKernel.h

lib-lua: LibFaceManager.cc FaceKernel.h
	g++ -shared -fPIC -o libfacemanagertest.so LibFaceManager.cc FaceKernel.h -lfacekerneltest

clean:
	rm *.so




# sudo ln -sf /home/seventh/workspace/openresty/cloud/image-classify/src/c_module/libfacekerneltest.so /usr/local/lib/libfacekerneltest.so

# sudo ln -sf /home/seventh/workspace/openresty/cloud/image-classify/src/c_module/libfacemanagertest.so /usr/local/lib/libfacemanagertest.so
