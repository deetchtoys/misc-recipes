#! /bin/bash

logfn=$1
analysis_tmp_file=/tmp/dns-analysis-tmp

egrep '\|Analysis\|(0000)' $logfn | sed 's/.*|Analysis|0000|\([^|]*\)|.*/\1/g'> $analysis_tmp_file

echo '99值: ' `datamash -t ' ' perc:99 1 < $analysis_tmp_file`
echo '95值: ' `datamash -t ' ' perc:95 1 < $analysis_tmp_file`
echo '90值: ' `datamash -t ' ' perc:90 1 < $analysis_tmp_file`
echo '85值: ' `datamash -t ' ' perc:85 1 < $analysis_tmp_file`
