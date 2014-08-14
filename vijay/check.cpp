#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
const LL N = 1000000+5;
LL a[N];
LL re(LL n, LL b)
{
   if(n <= b)return 1;

   if(n%b==0)
      return re(n/b, b)+1;
   else
      return re((n/b)+1, b)+1;
}
int main()
{
   LL te = 0;
   //freopen("input.txt", "r", stdin);
   LL n, S;
   while(scanf("%lld%lld", &S, &n))
   {
      ++ te;
      if(S==0 && n==0)break;

      for(LL i = 1; i <= n; ++ i)
         scanf("%lld", &a[i]);

      LL ma = a[0];
      for(LL i = 1; i <= n; ++ i)
      {
         if(a[i] > ma)
            ma = a[i];
      }
      if(ma==1)
      {

         printf("Case #%lld: 1\n", te);
         continue;
      }
      if(n >= 3)
      {
         if(re(ma, 2) <= S-ma)
         {
            printf("Case #%lld: 2\n", te);
         }
         else
         {
            printf("Case #%lld: 3\n", te);
         }
      }
      else
      {
         if(a[1] > a[2])
            swap(a[1], a[2]);
         LL s = 2, f = S, res;
         while(s <= f)
         {
            LL md = (s+f)/2;
            if(re(a[2], md) <= a[1])
            {
               res = md;
               f = md-1;
            }
            else
               s = md+1;
         }
         printf("Case #%lld: %lld\n", te, res);
      }
   }
   return 0;
}

