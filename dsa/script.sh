#!/bin/sh
INPUT_FILE=$1
OUTPUT_FILE=$2
MINCHARS=6
cat $INPUT_FILE | tr -s '\n' | grep -E ".{$MINCHARS}" | sort | uniq > $OUTPUT_FILE
