#!/usr/bin/env sh

input="$(cat input.txt)"
p1sum=
p2sum=
IFS='
'
for line in $input; do
	line="$(echo "$line" | tr ' \t' '\n' | sort -n)"

	# part 1: sum of differences between
	# largest and smallest number on every line
	low=$(echo "$line" | head -1)
	high=$(echo "$line" | tail -1)
	p1sum=$((p1sum + (high - low)))

	# part 2: sum of dividends between only 2
	# evenly divisible numbers on every line
	for i in $line; do
		for j in $line; do
			if [ $i -ne $j ]; then
				if [ $((i % j)) -eq 0 ]; then
					p2sum=$((p2sum + (i / j)))
				fi
			fi
		done
	done
done

echo "part 1: $p1sum"
echo "part 2: $p2sum"
