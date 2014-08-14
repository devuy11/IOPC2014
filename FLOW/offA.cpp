#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<cstring>
#include<list>
#include<map>
#include<queue>
#include<cassert>
#include<ctime>
using namespace std;
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a) memset(a,-1,sizeof(a))
#define pb push_back
#define MAX 100
#define MAXT 10000000
#define MAXF 10000
#define inf 1000000
//#pragma comment(linker,"/STACK:16777216")

int cap[2*MAX+5][2*MAX+5],prev[2*MAX+5],flow[2*MAX+5][2*MAX+5],N,n,clean[MAX+5][MAX+5];
vector<int> adj[2*MAX+5];
bool bfs(int s,int t){
	int i,u,v;
	SET(prev);
	prev[s]=-2;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		u=q.front();
		q.pop();
		int sz = adj[u].size();
		for(i=0;i<sz;i++){
		    v = adj[u][i];
			if(prev[v]==-1 && cap[u][v]>flow[u][v]){
				q.push(v);
				prev[v]=u;
			}
		}
	}
	return prev[t]==-1?false:true;
}
bool dinic(int s,int t){
	int i,u,v,flw;
	CLR(flow);
	while(bfs(s,t)){
		for(i=0;i<N;i++){
			if(prev[i]>=0 && cap[i][t] - flow[i][t]<=0) continue;
			flw=cap[i][t]-flow[i][t];
			for(v=i,u=prev[v];u>=0;v=u,u=prev[v]) flw=min(flw,cap[u][v]-flow[u][v]);
			for(v=i,u=prev[v];u>=0;v=u,u=prev[v]) {
				flow[u][v]+=flw;
				flow[v][u]-=flw;
			}
			flow[i][t]+=flw;
			flow[t][i]-=flw;

		}
	}
	for(i = 0;i<n;i++){
		if(cap[s][i+n]!=flow[s][i+n]) return false;
	}
	return true;
}
inline void addEdge(int x,int y,int c){
    cap[x][y]+=c;
    adj[x].pb(y);
    adj[y].pb(x);
}
int main(){

   // freopen("input.in","r",stdin);
    //freopen("output.ans","w",stdout);
//	double cl = clock();
    int t,cs=1,i,j,W,source,sink,ESOURCE,ESINK,mens,S[MAX+2],E[MAX+2];
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&mens);
        assert(1<=n && n<=MAX);
        assert(1<=mens && mens<=MAXF);
        int sum = 0;
        CLR(cap);
        N = 2*n + 4;
        for(i = 0;i<N;i++)
            adj[i].clear();
        source = 2*n;
        sink = 2*n + 1;
        ESOURCE = 2*n + 2;
        ESINK = 2*n + 3;
        for(i = 0;i<n;i++){
            scanf("%d %d %d",&S[i],&E[i],&W);
            assert(0<=S[i]  && S[i]<=E[i]);
            assert(E[i]<=MAXT);
            assert(1<=W && W<=MAXF);

            W = (W + mens - 1) / mens;
            sum+=W;
            addEdge(source,i,inf);
            addEdge(i+n,sink,inf);
            addEdge(ESOURCE,i+n,W);
            addEdge(i,ESINK,W);

        }
        for(i = 0;i<n;i++)
            for(j = 0;j<n;j++){
                scanf("%d",&clean[i][j]);
                assert(0<=clean[i][j] && clean[i][j] <=MAXT);
            }

        for(i = 0;i<n;i++){
            for(j = 0;j<i;j++){
                if(S[i]>E[j]+clean[j][i]){
                    addEdge(j+n,i,inf);

                }
                else if(S[j]>E[i]+clean[i][j]){
                    addEdge(i+n,j,inf);

                }
            }
        }
        addEdge(sink,source,0);
        int low = 0, hi = sum,mid,ans = -1;
		while(low<=hi){
			mid = (low+hi) / 2;
			cap[sink][source] = mid;
			if(dinic(ESOURCE,ESINK)){
				hi = mid - 1;
				ans = mid;
			}
			else low = mid+1;
		}
		assert(ans!=-1);
		printf("Case %d: %d\n",cs++,ans);
    }
/*
	cl = clock() - cl;
	fprintf(stderr,"Execution Time = %lf sec\n",cl / CLOCKS_PER_SEC);
*/
	return 0;
}
