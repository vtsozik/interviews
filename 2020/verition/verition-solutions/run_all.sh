#!/bin/sh

#set -ea

count=`ls -1 datasets | wc -l`

problem=1
while (( $problem <= $count ))
do
    echo ___________________________________________________; echo
    ./run.sh $problem
    problem=`expr $problem + 1`
done
