#include <bits/stdc++.h>

using namespace std;
typedef long long int LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> II;
typedef vector<II> VII;

#define PB push_back
#define MP make_pair
#define REP(i, n) for(int i = 0; i < n; i++)
#define FOR(i, p, k) for(int i = p; i <= k; i++)
#define REV(i, p, k) for(int i = p; i >= k; i--)
#define DBUG1(a) {printf("%s : ", #a); cout << a ; putchar('\n');}
const double EPS = ((double)(1e-9));
const LL INF = (1e9);

template <typename T> void DBUG2(T a, T b){
     while(a != b){cout << *a << " "; a++;}
     putchar('\n');
}

#define LIM 1000000
char inp[LIM];
VI seg, take;
int lreq, kreq;

void comp(){
     scanf("%s", inp);
     int len = strlen(inp);
     scanf("%d %d", &kreq, &lreq);
     seg = VI();
     take = VI();
     char prev = ' ';
     for(int i = 0; i < len; ){
          int c = 0;
          prev = inp[i];
          for(; i < len; i++){
               if(prev != inp[i]) break;
               c++;
          }
          seg.PB(c);
     }
     //DBUG2(seg.begin(), seg.end());
     int always = 0;
     REP(i, (int)seg.size()){
          if(seg[i] > kreq){
               always += kreq;
               seg[i] -= kreq;
          } else{
               always += seg[i];
               seg[i] = 0;
          }
          while(seg[i] > 0){
               if(seg[i] >= kreq){
                    seg[i] -= kreq;
                    take.PB(kreq);
               }
               else{   
                    take.PB(seg[i]);
                    seg[i] = 0;
               }
          }
     }
     sort(take.begin(), take.end());
     reverse(take.begin(), take.end());
     //DBUG2(take.begin(), take.end());

     int th = 0;
     while(always < lreq){
          always += take[th];
          th++;
     }

     printf("%d\n", lreq+th);
}

int main(int argc, char *argv[])
{
     int tcase;
     scanf("%d", &tcase);
     while(tcase--)
          comp();
     return 0;
}

