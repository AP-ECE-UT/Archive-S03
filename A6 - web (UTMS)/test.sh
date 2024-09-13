#!/bin/bash

TEST_CASES_DIR=./testcases
EXEC_NAME=./utgram
RUN_EXEC_CMD="$EXEC_NAME './csv/majors.csv' './csv/students.csv' './csv/courses.csv' './csv/teachers.csv'"
TMP_OUT_FILE=out.txt

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

touch $TMP_OUT_FILE

for file in $(find $TEST_CASES_DIR/ \( -name "*.txt" \) | sed "s/\.txt$//"); do
    if [[ $file != *Out ]]; then
        phase=$(echo $file | cut -d'/' -f3)
        input_file="$file".txt
        output_file="$file""Out.txt"

        run_cmd="$RUN_EXEC_CMD < $input_file > $TMP_OUT_FILE"

        eval $run_cmd

        diff -Bb $TMP_OUT_FILE $output_file

        if [ $? -ne 0 ]; then
            echo -e "${RED}✕ Failed Test $phase: $(basename "${input_file}" ".${input_file##*.}")${NC}"
            break
        else
            echo -e "${GREEN}✓ Passed Test $phase: $(basename "${input_file}" ".${input_file##*.}")${NC}"
        fi
    fi
done
