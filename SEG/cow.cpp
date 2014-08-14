#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define int64 long long
const int mod = (int) 1e9 + 7, S = 300;
using namespace std;

typedef int arr32[200010];
typedef int arrct[200010][4];

arr32 in, st, et, v, tot, size, flush;
arrct pre, p;
int n, m, d1, d2, d3, debug;

void reflush(int s)  {
	if (!flush[s])  return;
	int cnt = 0;  tot[s] = 0;
	for (int i = st[s]; i < et[s]; ++i)  {
		v[i] = (v[i] + p[s][0] + (int64) p[s][1] * cnt + (int64) p[s][2] * cnt * cnt + (int64) p[s][3] * cnt * cnt * cnt) % mod;
		tot[s] = (tot[s] + v[i]) % mod, ++cnt;
	}
	p[s][0] = p[s][1] = p[s][2] = p[s][3] = 0;
	flush[s] = false;
}
int ask(int s, int x, int y)  {
	reflush(s);
	int ret = 0;
	for (int i = x; i < y; ++i)  ret = (ret + v[i]) % mod;
	return ret;
}
int ask(int s)  {
	int sz = size[s];
	return (tot[s] + (int64) p[s][0] * pre[sz][0] + (int64) p[s][1] * pre[sz][1] + (int64) p[s][2] * pre[sz][2] + (int64) p[s][3] * pre[sz][3]) % mod;
}
int ask(int x, int y)  {
	int s = in[x], t = in[y + 1], ret = 0;
	if (s == t)  ret = ask(s, x, y + 1);
	else  {
		ret = (ask(s, x, et[s]) + ask(t, st[t], y + 1)) %  mod;
		for (int i = s + 1; i < t; ++i) ret = (ret + ask(i)) % mod;
		return ret;
	}
	return ret;
}
void rebuild(int s, int x, int y, int base)  {
	reflush(s);
	for (int i = x; i < y; ++i)  {
		tot[s] = (tot[s] - v[i] + mod) % mod;
		v[i] = (v[i] + d1 * base + (int64) d2 * base % mod * base % mod + (int64) d3 * base % mod * base % mod * base % mod) % mod, --base;
		tot[s] = (tot[s] + v[i]) % mod;
	}
}
void rebuild(int s, int base)  {
	int fr1 = base, fr2 = (int64) fr1 * base % mod, fr3 = (int64) fr2 * base % mod;
	p[s][0] = (p[s][0] + (int64) d1 * fr1 + (int64) d2 * fr2 + (int64) d3 * fr3) % mod;
	p[s][1] = ((p[s][1] - d1 - (int64) d2 * 2 * fr1 % mod - (int64) d3 * 3 * fr2 % mod) % mod + mod) % mod;
	p[s][2] = (p[s][2] + d2 + (int64) d3 * 3 * fr1 % mod) % mod;
	p[s][3] = (p[s][3] - d3 + mod) % mod;
	flush[s] = true;
}
void update(int x, int y, int d)  {
	d1 = d, d2 = d * d, d3 = d * d * d;
	int sta = max(y - n + x, 1), endt = y, base = x + min(n - x, y - 1) - 1;
	int s = in[sta], t = in[endt + 1];
	x = sta, y = endt;
	if (s == t)  rebuild(s, x, y + 1, base);
	else  {
		rebuild(s, x, et[s], base);  base -= et[s] - x;
		for (int i = s + 1; i < t; ++i)  rebuild(i, base), base -= et[i] - st[i];
		rebuild(t, st[t], y + 1, base);
	}
}
void prepare()  {
	int cnt = 0, sz = 0;
	for (int i = 1; i <= n + 1; ++i)  {
		if (++sz > S)  size[cnt] = sz - 1, sz = 1, et[cnt] = i, st[++cnt] = i;
		in[i] = cnt;
	}
	et[cnt] = n + 2, size[cnt] = sz;
	for (int i = 1; i <= S + 100; ++i)  {
		pre[i][0] = (pre[i - 1][0] + 1) % mod;
		pre[i][1] = (pre[i - 1][1] + i - 1) % mod;
		pre[i][2] = (pre[i - 1][2] + (i - 1) * (i - 1)) % mod;
		pre[i][3] = (pre[i - 1][3] + (i - 1) * (i - 1) * (i - 1)) % mod; 
	}
}
int main()  {
	int x, y, d;
	
	scanf("%d %d", &n, &m);
	prepare();
	
	for (int i = 1; i <= m; ++i)  {
		char ch;
		while (scanf("%c", &ch), ch != 'U'  &&  ch != 'Q');
		if (ch == 'U')  scanf("%d %d %d", &x, &y, &d), update(x, y, d);
		else  scanf("%d %d", &x, &y), printf("%d\n", ask(x, y));
	}
}

