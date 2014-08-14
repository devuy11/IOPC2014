#include <map>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <queue>
#include <utility>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

#define MAX 100000
#define Pair pair<int, int>

vector<int> primes;

bool isPrime(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int getperiod(int mod) {
    int a = 0, b = 1, c;
    int cnt = 1;
    while (a != 1 || b != 0) {
        c = (a + b) % mod;
        a = b;
        b = c;
        cnt++;
    }
    return cnt;
}

int calc(int n, int p) {
    int res = 0;
    int k = p;
    while (k <= n) {
        res += n / k;
        if (k > n / p) break;
        k *= p;
    }
    return res;
}

int comb(int n, int m, int mod) {
    long long r = 1;
    for (int i = 0; i < primes.size(); i++) {
        int cnt = calc(n, primes[i]) - calc(m, primes[i]) - calc(n - m, primes[i]);
        for (int j = 0; j < cnt; j++) r = r * primes[i] % mod;
    }
    return r;
}

vector<Pair> factor(int n) {
    vector<Pair> v;
    int cnt = 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }
            v.push_back(make_pair(i, cnt));
        }
    if (n > 1) v.push_back(make_pair(n, 1));
    return v;
}

int gcd(int a, int b) { if (a == 0 || b == 0) return a + b; if (a >= b) return gcd(a % b, b); else return gcd(b % a, a); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int getperiod2(int mod) {
    vector<Pair> v = factor(mod);
    if (v.size() == 1) return getperiod(mod);
    int p = 1;
    for (int i = 0; i < v.size(); i++) {
        int r = 1;
        for (int j = 0; j < v[i].second; j++) r *= v[i].first;
        p = lcm(p, getperiod(r));
    }
    return p;
}

int brute(int n, int m, int mod) {
    int nn = comb(n, m, 1000000000);

    int a = 0, b = 1, c;
    for (int i = 2; i <= nn; i++) {
        c = (a + b) % mod;
        a = b;
        b = c;
    }

    return b;
}

#define T int
int MOD;
typedef struct matrix{
    int row,col;
    T m[2][2];
    matrix(int r,int c,int k){
        row=r; col=c;
        for (int i=0;i<r;i++)
            for (int j=0;j<c;j++)
                m[i][j]=k;
    }
    matrix(int r){
        row=r; col=r;
        for (int i=0;i<r;i++)
            for (int j=0;j<r;j++)
                if (i==j) m[i][j]=1;
                else m[i][j]=0;
    }
    matrix(){}
}matrix;
matrix operator *(matrix &a,matrix &b){
    matrix c;
    T t;
    c.row=a.row; c.col=b.col;
    for (int i=0;i<c.row;i++)
        for (int j=0;j<c.col;j++){
            t=0;
            for (int k=0;k<a.col;k++)
                t=(t+1LL * a.m[i][k]*b.m[k][j])%MOD; // WARNING - Overflow
            c.m[i][j]=t;
        }
    return c;
}
matrix operator ^(matrix a,int k){
    matrix c(a.row);
    while(k > 0){
        if (k % 2) c=c*a;
        a=a*a;
        k /= 2;
    }
    return c;
}

int getfib(int n, int mod) {
    if (n <= 1) return n;
    matrix r = matrix(2);
    MOD = mod;
    r.m[0][0] = 1; r.m[0][1] = 1;
    r.m[1][0] = 1; r.m[1][1] = 0;
    r = r ^ (n - 1);

    return r.m[0][0];
}

int main()
{
    for (int i = 2; i <= MAX; i++) if (isPrime(i)) primes.push_back(i);
    srand(time(NULL));

    // freopen("F.in", "r", stdin);
    int TT;
    cin >> TT;
    while (TT--) {
        int n, m, mod;
        scanf("%d%d%d", &n, &m, &mod);
        // n = rand() % 20 + 1; m = rand() % n + 1; mod = 123127;

        int p = getperiod2(mod);
        int nn = comb(n, m, p);
        
        printf("%d\n", getfib(nn, mod));
        // if (brute(n, m, mod) != b) {
        //     printf("%d\n", p);
        //     printf("SHIT %d %d %d\n", n, m, mod);
        //     break;
        // }
    }
    // printf("PASSED\n");
    // system("pause");
    return 0;
}
