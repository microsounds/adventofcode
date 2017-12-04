#!/usr/bin/env sh

input=
if [ "$1" = "-" ]; then
	input="$(cat /dev/stdin)"
elif [ -z "$1" ] || [ ! -f "$1" ]; then
	echo "Input?" && exit 1
else
	input="$(cat "$1")"
fi

p1valid=0
p2valid=0
IFS='
'
for line in $input; do
	line="$(echo "$line" | tr ' ' '\n')"
	# part 1 -- no duplicate words
	if [ -z "$(echo "$line" | sort | uniq -d)" ]; then
		p1valid=$((p1valid + 1))
	fi
	# part 2 -- no anagrams allowed
	sorted=
	for word in $line; do # split, sort, and join
		word="$(echo "$word" | sed 's/./& /g' | tr ' ' '\n' | sort | tr '\n' ' ' | sed 's/ //g')"
		sorted="$sorted\n$word"
	done
	if [ -z "$(echo "$sorted" | sort | uniq -d)" ]; then
		p2valid=$((p2valid + 1))
	fi
done

echo "Part 1: $p1valid valid"
echo "Part 2: $p2valid valid"
