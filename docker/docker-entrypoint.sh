#! /bin/bash

pwd=`pwd`

proj_name=test

if [[ $TEST_WORKER_PROCESS_NUM ]]; then
    sed -i -e "s%<TEST_WORKER_PROCESS_NUM>%$TEST_WORKER_PROCESS_NUM%" ./conf/docker-nginx.conf
else
    sed -i -e "s%<TEST_WORKER_PROCESS_NUM>%1%" ./conf/docker-nginx.conf
fi

if [[ $SYSLOG_HOST ]]; then
    sed -i -e "s%<SYSLOG_HOST>%$SYSLOG_HOST%" ./conf/docker-nginx.conf
fi

if [[ $RESOLVER ]]; then
    sed -i -e "s%114.114.114.114%$RESOLVER%" ./conf/docker-nginx.conf
fi

if [[ $ERROR_LOCAL_NO ]]; then
    sed -i -e "s%<ERROR_LOCAL_NO>%$ERROR_LOCAL_NO%" ./conf/docker-nginx.conf
else
    sed -i -e "s%<ERROR_LOCAL_NO>%local1%" ./conf/docker-nginx.conf
fi

if [[ $ACCESS_LOCAL_NO ]]; then
    sed -i -e "s%<ACCESS_LOCAL_NO>%$ACCESS_LOCAL_NO%" ./conf/docker-nginx.conf
else
    sed -i -e "s%<ACCESS_LOCAL_NO>%local6%" ./conf/docker-nginx.conf
fi

echo "starting $proj_name"

exec "$@"
