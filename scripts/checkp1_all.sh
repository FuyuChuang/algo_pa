
for dir in "hw3_f"/*; do
    sid=$(basename $dir)
    command="./checkp1_person.sh "$sid""
    echo "================================================="
    echo "$command"
    eval $command
done
