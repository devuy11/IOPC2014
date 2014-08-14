echo "Enter the Name of your py code"
read main
echo "Enter the Name of the Folder in which output files will be stored"
read output
if [ -d $output ]; then
        rm -r $output
fi
mkdir $output
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
	time python $main < input/$i > $output/output$str.txt
	
done
