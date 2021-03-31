#! /bin/bash

function convert_string_to_array
{
    local oriIFS="$IFS"
    IFS=','
    converted_array=
    read -r -a converted_array <<< "$1"
    IFS="$oriIFS"
}

function watch_by_pidstat
{
    shift
    convert_string_to_array $1
    local command="pidstat"
    for item in ${converted_array[@]}; do
        if [[ $item != "" ]]; then
            command=$command" -p $item"
        fi
    done

    shift
    command=$command" $@ 1"
    eval $command
}

function watch_by_top
{
    shift
    convert_string_to_array $1
    local command="pidstat"
    for item in ${converted_array[@]}; do
        if [[ $item != "" ]]; then
            command=$command" -p $item"
        fi
    done

    shift
    command=$command" -d 1 $@"
    eval $command
}

if [[ $1 == "pidstat" ]]; then
    watch_by_pidstat $@
elif [[ $1 == "top" ]]; then
    watch_by_top $@
else
    echo 'unknown option, only support [pidstat|top]'
fi










#!/bin/bash

c=$1
n=$2

if [[ $c == '' ]]; then
    c=1
fi

if [[ $n == '' ]]; then
    n=1
fi

cd openresty

pwd=`pwd`
# ngx_command=$pwd/nginx/sbin/nginx
ngx_command=nginx

if [[ $c == 'stop' ]]; then
    pkill -9 "tail"
    if [[ -f $pwd/logs/nginx.pid ]]; then
        $ngx_command -p $pwd -c $pwd/conf/local.conf -s stop
    fi
elif [[ $c == 'result' ]]; then
    echo '正在分析数据，请稍等...'
    logfn=$pwd/logs/error.log
    costfn=$pwd/logs/cost.log
    rm -f $costfn
    egrep '\|Analysis\|(0001)' $logfn | sed 's/.*"recordId":"\([^"]*\).*"cost":\([^}]*\).*/\2 \1/g'> $costfn
    total_count=`grep 'Analysis' $logfn | egrep '\|0000' | wc -l`
    error_count=`grep 'Analysis' $logfn | egrep '\|1002' | wc -l`
    begin_time=`grep openresty $logfn | awk '{print $1,$2}'`
    end_time=`tail -n 1 $logfn | awk '{print $1,$2}'`
    echo '开始时间: ' $begin_time
    echo '结束时间: ' $end_time
    echo '总请求数: '$total_count
    if [[ $total_count > 0 ]]; then
        if [[ $error_count > 0 ]]; then
                echo "错误请求数: " $error_count
            echo $error_count" "$total_count | awk '{print "错误请求数占比: "$1/$2}'
        else
            echo "错误请求数占比: 0"
        fi

        awk '
            BEGIN {}

            {
              sum+=$1
              count+=1
              if($1>=3)
              {
                ge_3_counter+=1
              }
              if($1>=2)
              {
                ge_2_counter+=1
              }
              if($1>=1)
              {
                ge_1_counter+=1
              }
              if($1>=0.5)
              {
                ge_05_counter+=1
              }
              if($1>=0.3)
              {
                ge_03_counter+=1
              }
              if($1 < 0.3)
              {
                lh_03_counter+=1
              }
            }

            END {
              print "完成请求的数量: "count
              print "完成请求的总耗时: "sum
              print "大于等于3s的数量: "ge_3_counter
              print "大于等于2s的数量: "ge_2_counter
              print "大于等于1s的数量: "ge_1_counter
              print "大于等于0.5s的数量: "ge_05_counter
              print "大于等于0.3s的数量: "ge_03_counter
              print "小于0.3s的数量: "lh_03_counter
              print "响应时间大于3秒的请求占比: "ge_3_counter/count
              print "响应时间大于2秒的请求占比: "ge_2_counter/count
              print "响应时间大于1秒的时间占比: "ge_1_counter/count
              print "响应时间大于500毫秒的请求占比: "ge_05_counter/count
              print "响应时间大于300毫秒的请求占比: "ge_03_counter/count
              print "响应时间小于300毫秒的请求占比: "lh_03_counter/count
              print "响应时间均值: "sum/count
            }
' $costfn
        echo '95值: ' `datamash -t ' ' perc:95 1 < $costfn`
        echo '90值: ' `datamash -t ' ' perc:90 1 < $costfn`
        echo '85值: ' `datamash -t ' ' perc:85 1 < $costfn`
        delay_top10=`cat $costfn | sort -nr | head -n 10 | awk '{print $1}'`
        echo "延时top10: "
        echo $delay_top10
    fi
else
    echo "开始压测......"
    if [[ -f $pwd/logs/nginx.pid ]]; then
        echo "stop nginx process"
        $ngx_command -p $pwd -c $pwd/conf/local.conf -s stop 2>/dev/null
        sleep 1
    fi

    echo '' > $pwd/logs/error.log
    $ngx_command -p $pwd -c $pwd/conf/local.conf
    sleep 1
    curl "127.0.0.1:50011/test2-v2-full-link-pressure-test?c=$c&t=$n" 2>/dev/null
    sleep 1
    echo "start tail error.log"
    tail -f $pwd/logs/error.log | egrep 'Analysis' | egrep '(\|0001|\|0002)' | awk -F '|' '{print $4}'
fi



#!/bin/bash

c=$1
n=$2

if [[ $c == '' ]]; then
    c=1
fi

if [[ $n == '' ]]; then
    n=1
fi

cd openresty

pwd=`pwd`
# ngx_command=$pwd/nginx/sbin/nginx
ngx_command=nginx

if [[ $c == 'stop' ]]; then
    pkill -9 "tail"
    if [[ -f $pwd/logs/nginx.pid ]]; then
        $ngx_command -p $pwd -c $pwd/conf/local.conf -s stop
    fi
elif [[ $c == 'result' ]]; then
    echo '正在分析数据，请稍等...'
    logfn=$pwd/logs/error.log
    costfn=$pwd/logs/cost.log
    rm -f $costfn
    egrep '\|Analysis\|(0001)' $logfn | sed 's/.*"recordId":"\([^"]*\).*"cost":\([^}]*\).*/\2 \1/g'> $costfn
    total_count=`grep 'Analysis' $logfn | egrep '\|0000' | wc -l`
    error_count=`grep 'Analysis' $logfn | egrep '\|1002' | wc -l`
    begin_time=`grep openresty $logfn | awk '{print $1,$2}'`
    end_time=`tail -n 1 $logfn | awk '{print $1,$2}'`
    echo '开始时间: ' $begin_time
    echo '结束时间: ' $end_time
    echo '总请求数: '$total_count
    if [[ $total_count > 0 ]]; then
        if [[ $error_count > 0 ]]; then
                echo "错误请求数: " $error_count
            echo $error_count" "$total_count | awk '{print "错误请求数占比: "$1/$2}'
        else
            echo "错误请求数占比: 0"
        fi

        awk '
            BEGIN {}

            {
              sum+=$1
              count+=1
              if($1>=3)
              {
                ge_3_counter+=1
              }
              if($1>=2)
              {
                ge_2_counter+=1
              }
              if($1>=1)
              {
                ge_1_counter+=1
              }
              if($1>=0.5)
              {
                ge_05_counter+=1
              }
              if($1>=0.3)
              {
                ge_03_counter+=1
              }
              if($1 < 0.3)
              {
                lh_03_counter+=1
              }
            }

            END {
              print "完成请求的数量: "count
              print "完成请求的总耗时: "sum
              print "大于等于3s的数量: "ge_3_counter
              print "大于等于2s的数量: "ge_2_counter
              print "大于等于1s的数量: "ge_1_counter
              print "大于等于0.5s的数量: "ge_05_counter
              print "大于等于0.3s的数量: "ge_03_counter
              print "小于0.3s的数量: "lh_03_counter
              print "响应时间大于3秒的请求占比: "ge_3_counter/count
              print "响应时间大于2秒的请求占比: "ge_2_counter/count
              print "响应时间大于1秒的时间占比: "ge_1_counter/count
              print "响应时间大于500毫秒的请求占比: "ge_05_counter/count
              print "响应时间大于300毫秒的请求占比: "ge_03_counter/count
              print "响应时间小于300毫秒的请求占比: "lh_03_counter/count
              print "响应时间均值: "sum/count
            }
' $costfn
        echo '95值: ' `datamash -t ' ' perc:95 1 < $costfn`
        echo '90值: ' `datamash -t ' ' perc:90 1 < $costfn`
        echo '85值: ' `datamash -t ' ' perc:85 1 < $costfn`
        delay_top10=`cat $costfn | sort -nr | head -n 10 | awk '{print $1}'`
        echo "延时top10: "
        echo $delay_top10
    fi
else
    echo "开始压测......"
    if [[ -f $pwd/logs/nginx.pid ]]; then
        echo "stop nginx process"
        $ngx_command -p $pwd -c $pwd/conf/local.conf -s stop 2>/dev/null
        sleep 1
    fi

    echo '' > $pwd/logs/error.log
    $ngx_command -p $pwd -c $pwd/conf/local.conf
    sleep 1
    curl "127.0.0.1:50011/test2-full-link-pressure-test?c=$c&t=$n" 2>/dev/null
    sleep 1
    echo "start tail error.log"
    tail -f $pwd/logs/error.log | egrep 'Analysis' | egrep '(\|0001|\|0002)' | awk -F '|' '{print $4}'
fi
