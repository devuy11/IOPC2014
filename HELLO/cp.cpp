#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double R;
#define db 0
void eigen(int n, R m[n][n], R l[n], R vc[n][n]){R m2[n][n];
{int i=n; while(i--) {int j=n; while(j--) {m2[i][j] = m[i][j]; vc[i][j] = i==j;}}}
while(1){R mod = 0; int i=0, j=0;
{int k=n; while(k--){int m=n; while((--m)>k){R q = fabs(m2[k][m]);
  if(q > mod) {mod=q; i=k; j=m;}}}}
if(mod < 0.00000000001) break;
if(db) printf("mii=%e, mjj=%e\n", m2[i][i], m2[j][j]);
R th = 0.5*atan(2*m2[i][j]/(m2[i][i] - m2[j][j]));
if(db) printf("th=%e, i=%d, j=%d\n", th, i, j);
{R c = cos(th), s = sin(th);
void twst(R m[n][n]){int k=n; while(k--){R t = c*m[i][k]+s*m[j][k];
   m[j][k] = -s*m[i][k]+c*m[j][k]; m[i][k] = t;}}
{int k=n; while(k--){R t = c*m2[k][i] + s*m2[k][j];
   m2[k][j] = -s*m2[k][i] + c*m2[k][j]; m2[k][i]=t;}}
twst(m2); twst(vc);}}
{int j=n; while(j--) l[j] = m2[j][j];}}

#if 1
#define n 2
R x[][n] = {{2, 1}, {1, 2}};
R vec[n][n], vl[n];
int main(){
{int i=n; while(i--) {int j=n; while(j--)
   if(x[i][j] != x[j][i]) exit(printf("uns %d %d\n", i, j));}}
eigen(n, x, vl, vec);
int i; for(i=0; i<n; ++i){ printf("%11.7f: ", vl[i]);
   {int j; for(j=0; j<n; ++j) printf("%11.7f ", vec[i][j]); printf("\n");}}
{R me = 0; int j = n; while(j--){ // We examine the jth eigen vec and val.
    {int k = n; while(k--){ // We consider nth component of jth vec.
    R c = 0; {int y = n; while(y--) c += x[y][k]*vec[j][y];}
    {R e = fabs(vl[j]*vec[j][k] - c); if(e > me) me = e;}}}}
  printf("max error = %e\n", me);}
return 0;}
#endif
/*
R x[][n] = {{2, 1}, {1, 2}};
  3.0000000:   0.7071068   0.7071068 
  1.0000000:  -0.7071068   0.7071068 
max error = 1.110223e-16

R x[][n] = {{-1, 0, 0, -1}, {0, 1, 0, 0}, {0, 0, 1, 0}, {-1, 0, 0, -0.5}};
 -1.7807764:   0.7882054   0.0000000   0.0000000   0.6154122 
  1.0000000:   0.0000000   1.0000000   0.0000000   0.0000000 
  1.0000000:   0.0000000   0.0000000   1.0000000   0.0000000 
  0.2807764:  -0.6154122   0.0000000   0.0000000   0.7882054 
max error = 2.220446e-16

R x[][n] = {{1, .6, -1.1, -1.3}, {.6, -1.1, 2.1, .31}, {-1.1, 2.1, 2, 2}, {-1.3, .31, 2, 2}};
  1.3448669:   0.6563827   0.5095600   0.4533130  -0.3225177 
 -2.4988463:  -0.2643171   0.8275954  -0.4880947   0.0835820 
  5.0684407:  -0.3442539   0.2275122   0.6766162   0.6098508 
 -0.0144613:   0.6170798  -0.0606030  -0.3137857   0.7190816 
max error = 2.498002e-15

R x[][n] = {{1, .01, .4, 0}, {.01, -1.6, 0, 0}, {.4, 0, 2, 2}, {0, 0, 2, -0.7}};
  0.9538595:   0.9839759   0.0038529  -0.1135993  -0.1373748 
 -1.6000358:  -0.0035847   0.9999850  -0.0016985   0.0037742 
  3.1219800:   0.1647375   0.0003489   0.8739157   0.4573104 
 -1.7758036:   0.0681187  -0.0038747  -0.4726137   0.8786245 
max error = 8.790912e-12
*/
