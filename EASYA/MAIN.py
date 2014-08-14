test=int(raw_input())
for t in range(0,test):
	inp=raw_input().split(" ")
	a=int(inp[0])
	b=int(inp[1])
	q=0
	r=1
	for i in range(1,a+1):
		r=r*i
		#print r
		q=q*i
		q+=(r/b)
		q%=2
		r%=b
	if ( int(q==1) == 0 ):
		print "Even"
	else:
		print "Odd"
