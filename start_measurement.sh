#!/bin/bash

TEST_PROGRAM=$1
ITERATIONS=$2
MIN_DELAY=100000
MAX_DELAY=500000
PRE_DELAY=7
DATA_SUBDIRECTORY=$3

PATH_CLICK_SIMULATOR="click_simulator/bin/click_simulator"
PATH_LATENCY_TESTER="latency_tester/bin/latency_tester"
PATH_TEST_PROGRAM="test_programs/$TEST_PROGRAM/bin/$TEST_PROGRAM"
PATH_DATA="data/$DATA_SUBDIRECTORY/$TEST_PROGRAM.csv"

mkdir "data/$DATA_SUBDIRECTORY"

./$PATH_TEST_PROGRAM > /dev/null &
PID_TEST_PROGRAM=$!

sleep "1s"

./$PATH_CLICK_SIMULATOR $ITERATIONS $MIN_DELAY $MAX_DELAY $PRE_DELAY > /dev/null &
PID_CLICK_SIMULATOR=$!

sleep "1s"

EVENT=$(cat /proc/bus/input/devices | grep "autoclicker" -A 4 | grep event | awk '{split($2,a,"="); print a[2]}')
EVENT="/dev/input/$EVENT"

./$PATH_LATENCY_TESTER $EVENT $TEST_PROGRAM > $PATH_DATA &
PID_LATENCY_TESTER=$!

# could be used to move cursor to specified position
#xdotool mousemove $x $y

sigint() {
    kill -INT $PID_CLICK_SIMULATOR
    kill -INT $PID_LATENCY_TESTER
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT
wait $PID_CLICK_SIMULATOR

kill -TERM $PID_LATENCY_TESTER
kill -INT $PID_TEST_PROGRAM
