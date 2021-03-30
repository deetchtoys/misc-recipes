cat /tmp/hw_raw | awk '{split($0,a,"client: ");split(a[2],b,",");arr[b[1]]++;}END{for(k in arr){print k"\t"arr[k]}}' | sort -n -r



ll | egrep test.log | egrep '(20190401)' | awk '{print $9}' | xargs zgrep '278571900' | egrep 'QPS' | awk '{print $1}' | sed 's/[^:]*:\(.*\)/\1/g' | uniq -c | sort -n





ll | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'

ll | egrep test.log | egrep (20181112|20181113|20181114|20181115|20181116|20181117|20181118) | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'


egrep -nr 'ailog' test.log-2018111912 | awk '{print $12}' | awk -F '|' '{print $4}' | sort -u



ll | egrep test.log | egrep '(20181112|20181113|20181114|20181115|20181116|20181117|20181118)' | \
awk '{fileName=$9; if(fileName != ""){print fileName;system("zgrep \"QPS\" "fileName" | awk \"{print $12}\" | awk -F \"|\" \"{print $4}\"  >>/tmp/logs/duiserver-201811112-20181118.log")}}'



ll | egrep test.log | egrep '(20181112|20181113|20181114|20181115|20181116|20181117|20181118)' | \
awk '{fileName=$9; if(fileName != ""){system("zgrep \"QPS\" "fileName"")}}' | \
awk '{print $12}' | \
awk -F '|' '{print $8}' | \
sed 's/.*productId":"\([^"]*\)".*/\1/g' >> /tmp/logs/duiserver-201811112-20181118.log



ll | egrep test.log | egrep '20181112' | \
awk '{fileName=$9; if(fileName != ""){system("echo "fileName"")}}' | \
awk '{print $0"2rd"}' | \
awk -F '|' '{print $0"3rd"}'



ll | egrep test.log | egrep '(20181210|20181211|20181212|20181213|20181214|20181215|20181216)' | \
awk '{fileName=$9; if(fileName != ""){system("zgrep \"qa.lua\" "fileName" | egrep \"cloud-es-crud-agent.cloud.svc.cluster.local\" ")}}' | \
sed 's/.*productId=\([^&]*\).*/\1/g' >> /tmp/logs/qa-20181210-20181216.log



ll | egrep test.log | egrep '(20181119|20181120|20181121|20181122|20181123|20181124|20181125)' | \
awk '{fileName=$9; if(fileName != ""){cat fileName}}' | \
sed 's/.*productId=\([^&]*\).*/\1/g' >> /tmp/logs/qa-20181119-20181125.log


ll | egrep test.log | egrep (20181112|20181113|20181114|20181115|20181116|20181117|20181118) | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'







#! /bin/bash

function query_pids_by_ppids
{
    local awk_ppid_list=$1
    local command="ps -ef | egrep nginx | egrep -v grep | egrep -v nginx-find-proc | \
    awk '
        BEGIN {
            ppid_list_length=split(\"$awk_ppid_list\",ppid_list,\",\")
        }

        {
            for(ppid in ppid_list)
            {
                if(ppid_list[ppid] != \"\" && \$3 == ppid_list[ppid])
                {
                    pids=pids\$2\",\"
                }
            }
        }

        END {
            print(pids)
        }

        '
        "
    found_pids=`eval $command`
}

## 查询nginx master pids
function query_master_pids
{
    local nginx_master_ppid=$1
    query_pids_by_ppids $nginx_master_ppid
    nginx_master_pids=$found_pids
}

## 查询nginx worker pids
function query_worker_pids
{
    local nginx_master_pids=$1
    query_pids_by_ppids $nginx_master_pids
    nginx_workers_pids=$found_pids
}

## 查询nginx calculation pids
function query_calculation_pids
{
    local nginx_workers_pids=$1
    query_pids_by_ppids $nginx_workers_pids
    nginx_calculation_pids=$found_pids
}


nginx_master_pids=
nginx_workers_pids=
nginx_calculation_pids=
if [[ $# == 1 ]]; then
    nginx_master_pids=$1
    query_worker_pids $1
    query_calculation_pids $nginx_workers_pids
else
    query_master_pids 1
    query_worker_pids $nginx_master_pids
    query_calculation_pids $nginx_workers_pids
fi

echo nginx_master_pid: $nginx_master_pids
echo nginx_workers_pids: $nginx_workers_pids
echo nginx_calculation_pids: $nginx_calculation_pids




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
