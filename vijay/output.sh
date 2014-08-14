if [ -d "input" ]; then
	rm -r input
fi

if [ -d "output" ]; then
        rm -r output
fi

mkdir input
mkdir output
g++ -o test test_case.cpp
g++ -o main main.cpp
./test
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
rm test
rm main

