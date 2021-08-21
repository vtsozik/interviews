#!/bin/sh

if [ $# -eq 0 ]; then
    echo usage: `basename $0` problem-number
    echo example: `basename $0` 1
    exit 1
fi

set -ea
ARG=$1
EXEC=problem${ARG}
echo "Building executable $EXEC..."
make $EXEC

echo
echo "Running test cases with $EXEC..."

for i in datasets/$EXEC/*
do
    set -ea
    echo "Test case: $i"
    ./bin/$EXEC < $i >/tmp/output
    SOLUTION=`echo $i | sed -e "s/dataset/solution/g;s/in/out/g"`
    set +e
    diff $SOLUTION /tmp/output >/tmp/diff 2>&1
    if [ $? -eq 0 ]
    then
        echo "PASSED"
    else
        echo "FAILED"
        echo __________________
        echo
        echo "Diff:"
        cat /tmp/diff
        echo __________________
        echo
        echo "Program Output:"
        cat /tmp/output
        echo __________________
        echo
        echo "Correct Solution:"
        cat $SOLUTION
        echo __________________
        echo
    fi
done
