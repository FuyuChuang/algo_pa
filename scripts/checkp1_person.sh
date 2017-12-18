#!/usr/bin/env bash

################################################################################
# FileName  [ run.sh ]
# Synopsis  [ Test all output at once. ]
# Author    [ Fu-Yu Chuang ]
# Date      [ 2017.12.10 ]
################################################################################

exe="./checker"
name="$1"

if [[ "$#" -ne 1 ]]; then
    echo "Usage "$0" <student id>"
    exit 1
fi

grade="$name"

for testcase in "testcase1"/*; do
    case_name=$(basename $testcase)
    program_output="hw3_f/"$name"/output1/"$case_name".out"
    command=""$exe" "$testcase" "$program_output""
    echo "$command"
    result="$($command)"
    grade=""$grade" "$result""
done
printf '%s\n' $grade | paste -sd ',' >> grade.csv
