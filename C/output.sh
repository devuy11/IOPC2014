
if [ -d "output" ]; then
        rm -r output
fi

mkdir output
g++ -o main main.cpp
let s=0
for i in $( ls -1 "input");do
	if [ $s -lt 10 ]
	then
		str="0"
		str="$str$s"
	else
		str="$s"
	fi
	let s=s+1
	time ./main < input/$i > output/output$str.txt
done
