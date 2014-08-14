#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;

typedef list<int>	li;
typedef vector<int> vi; 
typedef vector<vi> vvi; 
typedef pair<int,int> ii; 
#define MAXX 10000000
#define FOR(i,n)	for(i=0;i<n;i++)
#define pi(n)		printf("%d\n",n);
#define pl(n)		printf("%lld\n",n);
#define pf(n)		printf("%lf\n",n);
#define ps(c)		printf("%s\n",c);
#define si(n)		scanf("%d",&n);
#define sl(n)		scanf("%lld",&n);
#define ss(n)		scanf("%s",n);
#define sf(n)		scanf("%lf",&n);
#define sc(n)		scanf(" %c",&n);
#define sz(a) 		int((a).size()) 
#define pb 			push_back 
#define all(c) 		(c).begin(),(c).end() 
#define tr(c,i) 	for(typeof((c).begin() i = (c).begin(); i != (c).end(); i++) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())

int neg(int a, int k)
{
	if(a <0)
		return ((a%k +k)%k);	//( (n%x) + x) %x
	else 
		return a%k;
}
int main()
{
	long long t,n,a,b,c,d,k,q1;
	int i;
	int global=0;
	bool flag1,flag2,flag3;
	long long s;
	sl(t);
	while(t--)
	{
		sl(n)
		sl(a)
		sl(b)
		sl(c)
		sl(d)
		sl(k)
		sl(q1)
		int *vis_k = new int[k];
		int *vis_d = new int[d];
		FOR(i,k)
			vis_k[i] = -1;
		FOR(i,d)
			vis_d[i] = -1;

		list<long long> q;
		vis_k[neg(n,k)] = 0;
		q.push_back(n);
		global = 0;
		while(!q.empty())
	 	{
	 		s = q.front();
	 		if(neg(s,k) == neg(q1,k))
	 		{
	 			break;
	 		}
	 		flag1 = false;
	 		flag2 = false;
	 		flag3 = false;
	 		q.pop_front();
	 		if(vis_k[neg(s+a,k)] == -1)
	 		{
	 			q.push_back(s+a);
	 			vis_k[neg(s+a,k)] = global+1;
	 			flag1 = true;
	 	//		printf("1Answer for v[%d] = %d\n",(s+a)%k,vis_k[(s+a)%k]);
	 		}
	 		if(vis_k[neg(s-b ,k)] == -1)
	 		{
	 			q.push_back(s-b);
	 			vis_k[neg(s-b,k)] = global+ 1;
	 			flag2 = true;
	 	//		printf("3Answer for v[%d] = %d\n",(s-b)%k,vis_k[(s-b)%k]);
	 		}
	 		if(vis_k[neg(s*c,k)] == -1)
	 		{
	 			q.push_back(s*c);
	 			vis_k[neg(s*c,k)] = global+ 1;
	 			flag3 = true;
	 	//		printf("5Answer for v[%d] = %d\n",(s*c)%k,vis_k[(s*c)%k]);
	 		}
	 		if(vis_k[neg(neg(s,d),k)] == -1)
	 		{
	 			q.push_back(neg(s,d));
	 			vis_k[neg(neg(s,d),k)] = global+ 1;
	 			vis_d[neg(s,d)] = 1;

	 	//		printf("Answer for v[%d] = %d\n",(s)%d%k,vis_k[(s)%d%k]);
	 		}
	 		if(!flag1)
	 		{
	 			if(vis_d[neg(s+a,d)] == -1)
	 			{
	 				q.push_back(neg(s+a,d));
	 				if(vis_k[neg(neg(s+a,d),k)] != -1)
	 					vis_k[neg(neg(s+a,d),k)] = min(vis_k[neg(neg(s+a ,d),k)], global+2);
	 				else
	 					vis_k[neg(neg(s+a,d),k)] = global+2;
	 				vis_d[neg(s+a ,d)] = 1;

	 	//		printf("2Answer for v[%d] = %d\n",(s+a)%d%k,vis_k[(s+a)%d%k]);
	 			}
	 		}
	 		
	 		if(!flag2)
	 		{
	 			if(vis_d[neg(s-b, d)] == -1)
	 			{
	 				q.push_back(neg(s-b,d));
	 				if(vis_k[neg(neg(s-b,d), k)] != -1)
	 					vis_k[neg(neg(s-b,d),k)] = min(vis_k[neg(neg(s-b,d),k)], global+2);
	 				else
	 					vis_k[neg(neg(s-b, d) ,k)] = global+2;
	 				vis_d[neg(s-b,d)] = 1;

	 	//		printf("4Answer for v[%d] = %d\n",(s-b)%d%k,vis_k[(s-b)%d%k]);
	 			}
	 		}
	 		
	 		if(!flag3)
	 		{
	 			if(vis_d[neg(s*c,d)] == -1)
	 			{
	 				q.push_back(neg(s*c,d));
	 				if(vis_k[neg(neg(s*c,d),k)] != -1 )
	 				{
	 					vis_k[neg(neg(s*c,d),k)] = min(vis_k[neg(neg(s*c,d),k)], global+2);
	 				}
	 				else
	 					vis_k[neg(neg(s*c,d),k)] = global +2;
	 				vis_d[neg(s*c,d)] = 1;

	 	//		printf("6Answer for v[%d] = %d\n",(s*c)%d%k,vis_k[(s*c)%d%k]);
	 			}
	 		}

	 		
	 		global++;
	 	}
	 	pi(vis_k[neg(q1,k)])

//	 	delete[] vis_k;
//	 	delete[] vis_d;
	}
	return 0;
}
