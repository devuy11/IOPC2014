#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <cassert>
 
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef double D;
typedef float F;
 
#define FOR(i,start,times) for(int i=start;i<start+times;++i)
#define gl(x) cin>>x
#define pls(x) cout<<x<<" "
#define pln(x) cout<<x<<"\n"
#define maxi(a,b) return a>b?a:b;
#define mini(a,b) return a>b?b:a;
 
/**************** My functions **********/
int abs(int a){
return a>0?a:-a;
}
 
bool mycompare (int i,int j){
return (i<j);
}
 
struct st{
int no;
int value;
};
 
bool compare(const st& lhs,const st& rhs){
if (lhs.value>rhs.value) return true;
return false;
}
 
ll modular_add(ll a,ll b,ll c){
ll res;
if (a + b < 0)
res=(a + b) + c;
else if (a + b >= c)
res=a + (b - c);
else
res= a + b;
return res;
}
 
ll modular_multi(ll a,ll b,ll c){
if(a>b){
ll tmp=b;
b=a;
a=tmp;
}
if(a==0||b<c/a)
return (a*b)%c;
ll res=0;
while(a>0){
if((a&1)==1){
res=(res+b)%c;
}
a=a>>1;
b=b-(c-b);
if(b<0){
b=b+c;
}
}
return res;
}
 
/************** Today's job ********/
 
 
int main(){
	int t,n,m,T[55][55],flag=0,total;
	st N[55];
	st M[55];
	scanf("%d",&t);
	total=t;
	while(t--){
		for(int i=0;i<55;i=i+1){
			N[i].no=N[i].value=0;
			M[i].no=M[i].value=0;
		}
		for(int i=0;i<55;i=i+1)
			for(int j=0;j<55;j++)
				T[i][j]=0;
		flag=0;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%d",&N[i].value);
			N[i].no=i;
		}
		for(int i=0;i<m;i++){
			scanf("%d",&M[i].value);
			M[i].no=i;
		}	
		int x=0;	
		sort(N,N+n,compare);
		while(N[x].value){
			sort(M,M+m,compare);
			int y=0;
			while(M[y].value&&N[x].value){
				T[N[x].no][M[y].no]=1;
				N[x].value=N[x].value-1;
				M[y].value=M[y].value-1;
				y++;
			}
			x++;
		}
		for(int i=0; i<n; i++)
			if(N[i].value){flag=1;break;}
		for(int i=0; i<m; i++)
			if(M[i].value){flag=1;break;}
		if(flag){
			printf("TestCase #:%d\n",total-t);
			printf("%d\n",-1);
		}
		else{
			flag=0;
			for(int ii=0;ii<n;ii++){
				for(int jj=0;jj<m;jj++){
					if(T[ii][jj]){
						for(int kk=n-1;kk>ii;kk--){
							if(T[kk][jj]==0){
								for(int ll=m-1;ll>jj;ll--){
									if(T[kk][ll]){
										if(T[ii][ll]==0){
											T[ii][jj]=0;
											T[ii][ll]=1;
											T[kk][jj]=1;
											T[kk][ll]=0;
											flag=1;
											break;
										}
									}
								}
								if(flag){flag=0; break;}
							}
						}
					}
				}
			}
			for(int ii=n-1;ii>=0;ii--){
				for(int jj=m-1;jj>=0;jj--){
					if(T[ii][jj]){
						for(int kk=n-1;kk>ii;kk--){
							if(T[kk][jj]==0){
								for(int ll=m-1;ll>jj;ll--){
									if(T[kk][ll]){
										if(T[ii][ll]==0){
											T[ii][jj]=0;
											T[ii][ll]=1;
											T[kk][jj]=1;
											T[kk][ll]=0;
											flag=1;
											break;
										}
									}
								}
								if(flag){flag=0; break;}
							}
						}
					}
				}
			}
			printf("TestCase #:%d\n",total-t);
			for(int i=0;i<=n-1;++i){
				for(int j=0;j<=m-1;++j){
					printf("%d",T[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}
