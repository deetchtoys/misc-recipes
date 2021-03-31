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
