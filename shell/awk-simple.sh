#! /bin/bash

cat /tmp/hw_raw | awk '{split($0,a,"client: ");split(a[2],b,",");arr[b[1]]++;}END{for(k in arr){print k"\t"arr[k]}}' | sort -n -r


ll | egrep test.log | egrep '(20190401)' | awk '{print $9}' | xargs zgrep '278571900' | egrep 'QPS' | awk '{print $1}' | sed 's/[^:]*:\(.*\)/\1/g' | uniq -c | sort -n

ll | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'

ll | egrep test.log | egrep '(20181112|20181113|20181114|20181115|20181116|20181117|20181118)' | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'


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

ll | egrep test.log | egrep '(20181112|20181113|20181114|20181115|20181116|20181117|20181118)' | awk '{fileName=$9; if(fileName != ""){print fileName;system("egrep -nr \"18\" "fileName">>total.log")}}'
