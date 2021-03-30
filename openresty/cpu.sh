#! /bin/bash


if [ ! -n "$1" ];then
    echo 'usage: ./perf.sh file_name'
    exit 1
fi

server=olive

masterId=$(ps -ef | grep $server | grep -v 'grep' | awk '{print $2}')

workerId=$(ps -ef | grep $masterId | grep -v 'grep' | grep -v $server | awk '{print $2}')

bt=$1_bt.bt
/openresty-systemtap-toolkit/ngx-sample-lua-bt -p $workerId --luajit20 -t 100 > $bt

fixbt=$1_fixbt.bt
echo $fixbt

/openresty-systemtap-toolkit/fix-lua-bt $bt > $fixbt

cbt=$1_cbt.cbt
echo $cbt

/FlameGraph/stackcollapse-stap.pl $fixbt > $cbt

svg=$1_svg.svg
echo $svg

/FlameGraph/flamegraph.pl $cbt > $svg
