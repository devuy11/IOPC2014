#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <iterator>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <ctime>
#pragma comment(linker, "/STACK:16777216")
using namespace std;

typedef long long int LL;
const int N=1001005;
const int M=555555;
const int INF=0x3f3f3f3f;
const double PI=acos(-1.0);
const double eps=1e-7;
int a,b,c,d,p;
int n,m,k,km;
int ans;
bool vis[N];
struct xh
{
    int yu,step;
  //string s;
}w,e,q[N];

void BFS()
{
    int he=0,ta=0;
    memset(vis,0,sizeof(vis));
    w.yu=(n%km+km)%km;
    w.step=0;
    //w.s="";
    q[ta++]=w;
    vis[w.yu]=1;
    while(he!=ta)
    {
        e=q[he++];
        if((e.yu%k+k)%k==ans)
        {
            cout<<e.step<<endl;
            //cout<<e.s<<endl;
            return ;
        }

        w=e;
        w.yu=((w.yu+a)%km+km)%km;
        if(!vis[w.yu])
        {
            vis[w.yu]=1;
            //      w.s+='+';
            w.step++;
            q[ta++]=w;
        }


        w=e;
        w.yu=((w.yu-b)%km+km)%km;
        if(!vis[w.yu])
        {
            vis[w.yu]=1;
            //w.s+='-';
            w.step++;
            q[ta++]=w;
        }

        w=e;
        w.yu=((w.yu*c)%km+km)%km;
        if(!vis[w.yu])
        {
            vis[w.yu]=1;
            //w.s+='*';
            w.step++;
            q[ta++]=w;
        }

        w=e;
        w.yu=(w.yu%m+km)%km;
        if(!vis[w.yu])
        {
            vis[w.yu]=1;
            //w.s+='%';
            w.step++;
            q[ta++]=w;
        }
    }
    puts("-1");
}

int main()
{
     int tcase;
     scanf("%d", &tcase);
     
     while(tcase--)
     {
          LL t;
          cin >> n >> a >> b >> c >> m >> k >> p;
          d = m;
          if(n==0&&k==0&&m==0)
               break;
          km=k*m;
          ans=((p)%k+k)%k;
          BFS();
     }
     return 0;
}

