#!/usr/bin/env bash

################################################################################
# FileName  [ run.sh ]
# Synopsis  [ Run all testcase at once. ]
# Author    [ Fu-Yu Chuang ]
# Date      [ 2017.12.10 ]
################################################################################

exe="./scheduler"
input_dir="$1"
output_dir="$2"

if [[ "$#" -ne 2 || ! -d "$1" || ! -d "$2" ]]; then
    echo "Usage "$0" <input dir> <output dir>"
    exit 1
fi

for input in "$input_dir"/*; do
    input_name=$(basename $input)
    command=""$exe" "$input""
    echo "$command"
    result="$($command)"
    echo "$result" > "$output_dir"/"$input_name".out
    echo ""
done
