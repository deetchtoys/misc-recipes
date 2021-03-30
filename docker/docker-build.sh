#! /bin/bash

image_name=test
image_tag=''
if (($# == 1)); then
    image_tag=$1
else
    echo "missing image_tag"
    exit 1
fi

# prepare
rm -rf build
mkdir -p build/$image_name
mkdir -p build/$image_name/logs

# build src files of docker image
cp -fr lualib luaclib conf src bin          build/$image_name/
cp -fr docker-entrypoint.sh                 build/$image_name/
cp -fr Dockerfile                           build

if [[ $image_tag == private* ]]; then
    export LUA_PATH=`pwd`/tools/luajit/share/luajit-2.1.0-beta3/?.lua
    luajit=./tools/luajit/bin/luajit
    for file in $(find build/$image_name/ -type f -name "*.lua")
    do
        if test -f $file
        then
            $luajit -b $file $file
            if [[ $? -ne 0 ]]; then
                echo "build $file failed."
                exit 1
            fi
            echo $file
        fi
    done
fi

# build
docker build \
       --force-rm -t $image_name:$image_tag \
       --build-arg PROJ_NAME=$image_name\
       ./build
