#!/bin/bash

image_name=test
image_tag=$1

resolver=114.114.114.114
syslog_host=127.0.0.1
error_local_no=local1

docker run -d -p 27777:37777                                                                         \
       -e RESOLVER=$resolver                                                                              \
       -e SYSLOG_HOST=$syslog_host                                                                        \
       -e ERROR_LOCAL_NO=$error_local_no                                                                  \
       $image_name:$image_tag
