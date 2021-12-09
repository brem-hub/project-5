#!/bin/bash

program_name=$(ls bin/)

programs=$(ps aux | grep $program_name | grep -v "grep" | grep -v "$(basename "$0")" | awk '{print $2}' | uniq) # | wc -l)

if [[ $programs -eq "" ]]
then
    echo "No lauched processes with name \`$program_name\`"
else
    if [[ $(echo $programs | wc -l) -eq 1 ]]
    then
        kill -SIGINT $programs
        echo "Killing pid $programs"
    else
        echo "Cannot kill program as there are other processes that have the same name"
    fi
fi


