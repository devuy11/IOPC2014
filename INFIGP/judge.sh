function comp(){
	local add="/"
	local file1="$2$add$1"
	local file2="$3$add$1"
	cp $file1 m1
	cp $file2 m2
	sed -i '/^$/d' m1
	sed -i '/^$/d' m2
	A=`cat m1`
	B=`cat m2`
	if [ "$A" == "$B" ]
	then 
		echo "Correct Answer"
	else
		echo "Wrong Answer"
	fi
	rm m1
	rm m2
}

echo "Enter Folder 1"
read main
echo "Enter Folder 2"
read brute

for i in $( ls -1 $main ); do
	for j in $(ls -1 $brute);do
		if [ $i == $j ];then
			comp $i $main $brute
		fi
	done
done
