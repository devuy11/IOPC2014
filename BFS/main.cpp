#include<stdio.h>
#include<algorithm>
#include<queue>
#include<stdlib.h>
#include<string.h>
#include<utility>
using namespace std;
bool visited[1000001];
int n,a,b,c,d,k,q,z;
int bfs()
{
	z=k*d;
	queue<pair<int,int> > myqueue;
	myqueue.push(make_pair(n%(k*d),0));
	visited[n%(k*d)]=true;
	pair<int,int> v;
	while(!myqueue.empty()){
		v=myqueue.front();
		myqueue.pop();
		if((v.first%k)==(q%k))	return v.second;
		if(!visited[(v.first+a)%z]){
			myqueue.push(make_pair((v.first+a)%z,v.second+1));
			visited[(v.first+a)%z]=true;
		}
		if(!visited[(((v.first-b)%z)+z)%z]){
                        myqueue.push(make_pair((((v.first-b)%z)+z)%z,v.second+1));
			visited[(((v.first-b)%z)+z)%z]=true;
                }
		if(!visited[(v.first*c)%z]){
                        myqueue.push(make_pair((v.first*c)%z,v.second+1));
			visited[(v.first*c)%z]=true;
                }
		if(!visited[(v.first%d)%z]){
                        myqueue.push(make_pair((v.first%d)%z,v.second+1));
			visited[(v.first%d)%z]=true;
                }
	}
	return -1;
}
void solve()
{
	int ans;
	scanf("%d%d%d%d%d%d%d",&n,&a,&b,&c,&d,&k,&q);
	memset(visited,0,sizeof(visited));
	n=n%(k*d);
	ans=bfs();
	//if(ans==-1){
	//	printf("%d %d %d %d %d %d %d\n",n,a,b,c,d,k,q);
	//}
	printf("%d\n",ans);
}
int main()
{
	int test;
	scanf("%d",&test);
	while(test--){
		solve();
	}
	return 0;
}
