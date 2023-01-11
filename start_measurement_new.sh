#!/bin/bash

TEST_PROGRAM=$1
TEST_PARAMS=$2
ITERATIONS=$3
DATA_SUBDIRECTORY=$4

PATH_TEST_PROGRAM="test_programs/$TEST_PROGRAM/bin/${TEST_PROGRAM}_${TEST_PARAMS}"
PATH_DATA="data/$DATA_SUBDIRECTORY/${TEST_PROGRAM}_${TEST_PARAMS}"

mkdir "data/$DATA_SUBDIRECTORY" 2> /dev/null

./$PATH_TEST_PROGRAM > /dev/null &
PID_TEST_PROGRAM=$!

sleep "1s"

python3 calibrate_yalmd.py

# could be used to move cursor to specified position
#xdotool mousemove $x $y

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python3 control_yalmd.py "${TEST_PROGRAM}_${TEST_PARAMS}" $ITERATIONS 1 "${PATH_DATA}_fw.csv"

python3 control_yalmd.py "${TEST_PROGRAM}_${TEST_PARAMS}" $ITERATIONS 0 "${PATH_DATA}_nofw.csv"

kill -9 $PID_TEST_PROGRAM
