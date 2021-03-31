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
