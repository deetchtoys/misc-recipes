#! /bin/bash

# prepare
rm -rf build
mkdir -p build/c-server
cp -rf bin/c-server build/c-server/bin/
cp -rf Dockerfile build

# build
docker build --force-rm -t seventhking/c-server:0.0.1 build
