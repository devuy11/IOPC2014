test=int(raw_input())
state=[[0 for x in xrange(2)] for x in xrange(2)]
mod=0
q=0
r=0
a=0
b=0
curr=0
prev=0
for t in range(0,test):
	str=raw_input()
	a=int(str.split(' ')[0])
	b=int(str.split(' ')[1])
	curr=1
	mod=b%2
	if((a==1 and  b==1) or (a==0 and b==1)):
		print "Odd"
		continue
	else:
		state[0][0]=0
		state[0][1]=1
		state[1][0]=0
		state[1][1]=0
		for i in range(2,a+1):
			prev=curr^1
			q=(state[prev][1]*i)/b
			r=(state[prev][1]*i)%b
			q%=2
			state[curr][0]=(state[prev][0]*i+q)%2
			state[curr][1]=r
			curr=curr^1
		prev=curr^1
		if(state[prev][0]==0):
			print "Even"
		else:
			print "Odd"
