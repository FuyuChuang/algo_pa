
for dir in "hw3_f"/*; do
    sid=$(basename $dir)
    command="./checkp2_person.sh "$sid""
    echo "================================================="
    echo "$command"
    eval $command
done
