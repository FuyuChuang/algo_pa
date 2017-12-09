#!/usr/bin/env bash

################################################################################
# FileName  [ run.sh ]
# Synopsis  [ Test all output at once. ]
# Author    [ Fu-Yu Chuang ]
# Date      [ 2017.12.10 ]
################################################################################

exe="./checker"
input_dir="$1"
output_dir="$2"
result_dir="$3"

if [[ "$#" -ne 3 || ! -d "$1" || ! -d "$2" || ! -d "$3" ]]; then
    echo "Usage "$0" <input dir> <output dir> <result dir>"
    exit 1
fi

for input in "$input_dir"/*; do
    input_name=$(basename $input)
    output_name=""$output_dir"/"$input_name".out"
    command=""$exe" "$input" "$output_name""
    echo "$command"
    result="$($command)"
    echo "$result"
    echo ""
done
