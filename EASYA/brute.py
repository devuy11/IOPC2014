def fact(n):
	if n<2:
		return 1
	return n*fact(n-1)
test=input()
for i in range(1,test):
	str=raw_input()
	a=int(str.split(' ')[0])
	b=int(str.split(' ')[1])
	if( (fact(a) / b)%2 == 0 ):
		print "Even"
	else:
		print "Odd"
