import java.io.*;
import java.util.*;

public class Main {

	static void solve() throws IOException {
		// int max = 100000;
		// int[] ok = precalc(max);
		// int[] iterations = new int[max + 1];
		// int maxIt = 0;
		// for (int i = 2; i <= max; i++) {
		// iterations[i] = iterations[ok[i]] + 1;
		// maxIt = Math.max(maxIt, iterations[i]);
		// }
		// System.err.println(maxIt);

		int n = nextInt();
		int queriesCount = nextInt();
		int[] edgeU = new int[n - 1];
		int[] edgeV = new int[n - 1];
		for (int i = 0; i < n - 1; i++) {
			edgeU[i] = nextInt() - 1;
			edgeV[i] = nextInt() - 1;
		}
		int[][] edges = new int[n][];
		{
			int[] deg = new int[n];
			for (int i = 0; i < n - 1; i++) {
				++deg[edgeU[i]];
				++deg[edgeV[i]];
			}
			for (int i = 0; i < n; i++) {
				edges[i] = new int[deg[i]];
			}
			Arrays.fill(deg, 0);
			for (int i = 0; i < n - 1; i++) {
				int u = edgeU[i], v = edgeV[i];
				edges[u][deg[u]++] = v;
				edges[v][deg[v]++] = u;
			}
		}
		DFSResult dfs = new DFSResult(edges, 0);
		for (int i = 0; i < n; i++) {
			int index = -1;
			for (int j = 0; j < edges[i].length; j++) {
				if (edges[i][j] == dfs.parent[i]) {
					index = j;
					break;
				}
			}
			if (index >= 0) {
				int[] newEdges = new int[edges[i].length - 1];
				System.arraycopy(edges[i], 0, newEdges, 0, index);
				System.arraycopy(edges[i], index + 1, newEdges, index,
						newEdges.length - index);
				edges[i] = newEdges;
			}
		}

		long[] value = new long[n];
		for (int i = 0; i < n; i++) {
			value[i] = nextLong();
		}
		int maxMod = 0;
		Query[] queries = new Query[queriesCount];
		for (int i = 0; i < queriesCount; i++) {
			char type = nextChar();
			int a, b, c;
			long d;
			if (type == 'Q') {
				a = nextInt() - 1;
				b = nextInt() - 1;
				c = nextInt();
				d = 0;
			} else {
				a = nextInt() - 1;
				b = 0;
				c = 0;
				d = nextLong();
			}
			maxMod = Math.max(maxMod, c);
			queries[i] = new Query(type, a, b, c, d);
		}
		int[] ok = precalc(maxMod);
		findLCAoffline(edges, 0, queries);
		PowerTowerSolver solver = new PowerTowerSolver(edges, ok, value,
				dfs.parent, dfs.timeIn);

		try {
		for (Query query : queries) {
			if (query.type != 'Q') {
				solver.value[query.x] = query.what;
				continue;
			}
			int u = query.x;
			int v = query.y;
			int lca = query.lca;
			int answer = solver.solvePowerTower(u, v, lca, query.mod);
			out.println(answer);
		}
		} catch(Exception e) {
			while (true);
		}
	}

	static class PowerTowerSolver {
		int[][] edges;
		int[] newMod;
		long[] value;
		int[] parent, timeIn;

		public PowerTowerSolver(int[][] edges, int[] newMod, long[] value,
				int[] parent, int[] timeIn) {
			this.edges = edges;
			this.newMod = newMod;
			this.value = value;
			this.parent = parent;
			this.timeIn = timeIn;
		}

		public int solvePowerTower(int u, int v, int lca, int mod) {
			return solvePowerTower1(u, v, lca, mod, 0) % mod;
		}

		int goUp(int u) {
			return parent[u];
		}

		int goDown(int u, int to) {
			int[] e = edges[u];
			int left = -1, right = e.length;
			while (right - left > 1) {
				int m = left + right >> 1;
				if (timeIn[e[m]] > timeIn[to]) {
					right = m;
				} else {
					left = m;
				}
			}
			return e[left];
		}

		static final int BIGENOUGH = 100;

		static int applyMod(long value, int mod) {
			if (value >= mod && value > BIGENOUGH) {
				value = applyModBig(value, mod);
			}
			return (int) value;
		}

		private static int applyModBig(long value, int mod) {
			value %= mod;
			if (value < BIGENOUGH) {
				value += (mod + BIGENOUGH - 1) / mod * mod;
			}
			return (int) value;
		}

		int solvePowerTower1(int u, int v, int lca, int mod, int depth) {
			if (value[u] == 0) {
				return 0;
			}
			if (u == v || value[u] == 1) {
				return applyMod(value[u], mod);
			}
			if (mod == 1 && depth >= 5) {
				return BIGENOUGH;
			}
			int uTo, lcaTo;
			if (u == lca) {
				uTo = goDown(u, v);
				lcaTo = uTo;
			} else {
				uTo = parent[u];
				lcaTo = lca;
			}
			int modTo = newMod[mod];
			int pow = solvePowerTower1(uTo, v, lcaTo, modTo, depth
					+ (mod == 1 ? 1 : 0));
			long base = value[u];
			if (pow < BIGENOUGH) {
				if (pow < 10) {
					int result = 1;
					for (int i = 0; i < pow; i++) {
						result = applyMod((long) result * base, mod);
					}
					return result;
				} else {
					int res = modPow((int) (base % mod), pow, mod);
					res = applyModBig(res, mod);
					return res;
				}
			} else {
				if (mod == 1) {
					return BIGENOUGH;
				}
				int mod1 = (int) (base % mod);
				for (int i = 0; i < 6; i++) {
					mod1 = mul(mod1, mod1, mod);
				}
				if (mod1 == 0) {
					return applyModBig(0, mod);
				}
				mod1 = gcd(mod1, mod);
				int mod2 = mod / mod1;

				int resMod2 = modPow((int) (base % mod), pow, mod2);
				int res = (int) ((long) resMod2 * mod1 * modInverse(mod1, mod2) % mod);
				res = applyModBig(res, mod);
				return res;
			}
		}
	}

	private static void findLCAoffline(int[][] edges, int root, Query[] queries) {
		int n = edges.length;
		int[] nextQuery = new int[queries.length * 2];
		int[] firstQuery = new int[n];
		Arrays.fill(firstQuery, -1);
		for (int it = 0; it < queries.length; it++) {
			Query query = queries[it];
			if (query.type != 'Q') {
				continue;
			}
			nextQuery[it * 2] = firstQuery[query.x];
			firstQuery[query.x] = it * 2;
			nextQuery[it * 2 + 1] = firstQuery[query.y];
			firstQuery[query.y] = it * 2 + 1;
		}
		int[] dsuAncestor = new int[n];
		DisjointSets dsu = new DisjointSets(n);
		int[] curEdge = new int[n];
		int[] stack = new int[n];
		int[] parent = new int[n];
		boolean[] was = new boolean[n];
		parent[root] = -1;
		stack[0] = root;
		int size = 1;
		for (int i = 0; i < n; i++) {
			dsuAncestor[i] = i;
		}
		while (size > 0) {
			int current = stack[size - 1];
			was[current] = true;
			if (curEdge[current] == edges[current].length) {
				for (int id = firstQuery[current]; id >= 0; id = nextQuery[id]) {
					Query query = queries[id >> 1];
					int other = query.x ^ query.y ^ current;
					if (was[other]) {
						query.lca = dsuAncestor[dsu.get(other)];
					}
				}
				if (parent[current] >= 0) {
					dsu.union(current, parent[current]);
					dsuAncestor[dsu.get(current)] = parent[current];
				}
				size--;
			} else {
				int next = edges[current][curEdge[current]++];
				if (was[next]) {
					continue;
				}
				parent[next] = current;
				stack[size++] = next;
			}
		}
	}

	static class Query {
		char type;
		int x, y, mod;
		long what;

		public Query(char type, int x, int y, int mod, long what) {
			this.type = type;
			this.x = x;
			this.y = y;
			this.mod = mod;
			this.what = what;
		}

		int lca;
	}

	static int mul(int a, int b, int MOD) {
		return (int) ((long) a * b % MOD);
	}

	static int modPow(int a, long pow, int MOD) {
		int res = 1 % MOD;
		while (pow > 0) {
			if ((pow & 1) != 0) {
				res = mul(res, a, MOD);
			}
			a = mul(a, a, MOD);
			pow >>= 1;
		}
		return res;
	}

	static long modInverse(long a, long mod) {
		extendedGcd(a, mod, temp);
		long res = temp[0];
		res %= mod;
		if (res < 0) {
			res += mod;
		}
		return res;
	}

	static long[] temp = new long[2];

	static long extendedGcd(long a, long b, long[] xy) {
		if (a == 0) {
			if (xy == null || xy.length != 2)
				throw new IllegalArgumentException();
			xy[0] = 0;
			xy[1] = 1;
			return b;
		}
		long d = extendedGcd(b % a, a, xy);
		long tmp = xy[0];
		xy[0] = xy[1] - (b / a) * xy[0];
		xy[1] = tmp;
		return d;
	}

	private static int[] precalc(int max) {
		int[] someDivisor = new int[max + 1];
		for (int i = 2; i * i <= max; i++) {
			if (someDivisor[i] == 0) {
				for (int j = i * i; j <= max; j += i) {
					someDivisor[j] = i;
				}
			}
		}
		int[] ok = new int[max + 1];
		ok[1] = 1;
		for (int i = 2; i <= max; i++) {
			if (someDivisor[i] == 0) {
				ok[i] = i - 1;
			} else {
				int p = someDivisor[i];
				int val = i;
				while (val % p == 0) {
					val /= p;
				}
				if (val == 1) {
					ok[i] = i - i / p;
				} else {
					int pPow = i / val;
					ok[i] = ok[pPow] / gcd(ok[pPow], ok[val]) * ok[val];
				}
			}
		}
		return ok;
	}

	static int gcd(int a, int b) {
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			} else {
				b %= a;
			}
		}
		return a | b;
	}

	static BufferedReader br;
	static PrintWriter out;

	public static void main(String[] args) throws IOException {
		InputStream input = System.in;
		PrintStream output = System.out;
		br = new BufferedReader(new InputStreamReader(input));
		out = new PrintWriter(output);
		solve();
		out.close();
	}

	public static int nextInt() throws IOException {
		int c = br.read();
		while ((c < '0' || c > '9') && c != '-')
			c = br.read();
		boolean negative = false;
		if (c == '-') {
			negative = true;
			c = br.read();
		}
		int m = 0;
		while (c >= '0' && c <= '9') {
			m = m * 10 + c - '0';
			c = br.read();
		}
		return negative ? -m : m;
	}

	public static long nextLong() throws IOException {
		int c = br.read();
		while ((c < '0' || c > '9') && c != '-')
			c = br.read();
		boolean negative = false;
		if (c == '-') {
			negative = true;
			c = br.read();
		}
		long m = 0;
		while (c >= '0' && c <= '9') {
			m = m * 10 + c - '0';
			c = br.read();
		}
		return negative ? -m : m;
	}

	public static char nextChar() throws IOException {
		int c = br.read();
		while (c <= ' ' && c >= 0) {
			c = br.read();
		}
		if (c < 0) {
			throw new EOFException();
		}
		return (char) c;
	}
}

class DisjointSets {
	private int[] p;

	public DisjointSets(int n) {
		p = new int[n];
		Arrays.fill(p, ~0);
	}

	public int get(int i) {
		int root = i;
		while (p[root] >= 0) {
			root = p[root];
		}
		while (i != root) {
			int ni = p[i];
			p[i] = root;
			i = ni;
		}
		return root;
	}

	public void union(int i, int j) {
		i = get(i);
		j = get(j);
		if (i == j) {
			return;
		}
		if (~p[i] < ~p[j]) {
			p[i] = j;
		} else {
			if (~p[i] == ~p[j]) {
				--p[i];
			}
			p[j] = i;
		}
	}

	public void clear() {
		Arrays.fill(p, ~0);
	}
}

class DFSResult {
	public final int[] timeIn;
	public final int[] parent;

	public DFSResult(int[][] edges, int root) {
		int n = edges.length;
		timeIn = new int[n];
		Arrays.fill(timeIn, -1);
		parent = new int[n];
		int[] curEdge = new int[n];
		int[] stack = new int[n];
		stack[0] = root;
		int size = 1;
		parent[root] = -1;
		timeIn[root] = 0;
		int index = 0;
		while (size > 0) {
			int current = stack[size - 1];
			if (curEdge[current] == edges[current].length) {
				size--;
			} else {
				int next = edges[current][curEdge[current]++];
				if (timeIn[next] >= 0) {
					continue;
				}
				parent[next] = current;
				timeIn[next] = ++index;
				stack[size++] = next;
			}
		}
	}
}

