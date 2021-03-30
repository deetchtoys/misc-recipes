all:mylib.so myArray.so Account.so myDir.so

mylib.so:mylib.c libHelperFuncs.so
	gcc mylib.c -std=c99 -fPIC -shared -lHelperFuncs -o mylib.so

myArray.so:myArray.c libHelperFuncs.so
	gcc myArray.c -std=c99 -fPIC -shared -lHelperFuncs -o myArray.so

Account.so:Account.c libHelperFuncs.so
	gcc Account.c -std=c99 -fPIC -shared -lHelperFuncs -o Account.so

myDir.so:myDir.c libHelperFuncs.so
	gcc myDir.c -std=c99 -fPIC -shared -lHelperFuncs -o myDir.so

libHelperFuncs.so:HelperFuncs.c HelperFuncs.h
	gcc HelperFuncs.c -std=c99 -fPIC -shared -o libHelperFuncs.so
	cp -f libHelperFuncs.so ~/mylib/so/

clean:
	rm -f myArray.so mylib.so libHelperFuncs.so Account.so
