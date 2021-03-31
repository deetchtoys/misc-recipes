#! /bin/bash

kill -9 `ps -ef | egrep nginx | egrep -v nginx-kill-proc | egrep -v egrep | awk '{print $2}' `
