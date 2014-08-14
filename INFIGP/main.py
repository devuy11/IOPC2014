from fractions import gcd


def rip(n):
	while(n%2==0):
		n=n/2
	return n
def ispow2(n):
	while(n%2==0):
		n=n/2
	return n==1

def which(n):
	ans=0
	while(n%2==0):
		n=n/2
		ans+=1
	return ans

test=int(raw_input())
for t in range(0,test):
	inp=raw_input().split(" ")
	p=int(inp[0])
	q=int(inp[1])
	g=gcd(p,q)
	p=p/g
	q=q/g

	cn=rip(p)
	cd=rip(q)

	if(cn!=1):	
		print "NO"
		continue

	if(ispow2(cd+1)==0):	
		print "NO"
		continue

	temp=(q/cd)*(cd+1)
	if(temp%p==0):
		temp/=p
		if(ispow2(temp)):
			print "YES"
		else:
			print "NO"

	else:
		print "NO"	
