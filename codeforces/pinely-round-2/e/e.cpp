#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " << 
#define sz(x) ((int) (x).size())
#define X first
#define Y second

#define MAX_N 100005

// define variables here
int n, m, k;
vector <pii > edges;
vii adj, rev; 
vi hs, value;
vector <bool> color;
vector <ll> fvalue;


vector <int> range(int n) {
	vector <int> indices(n);
	for (int i = 0; i < n; ++i) indices[i] = i;
	return indices;
}

void read_input() {
	cin >> n >> m >> k;
	hs.clear();
	for (auto i: range(n)) {
		int h; cin >> h;
		hs.push_back(h);
	}
	edges.clear();
	for (auto i: range(m)) {
		int u, v; cin >> u >> v;
		edges.push_back({u - 1, v - 1});
	}
	// trace(hs[0] _ hs[1] _ sz(edges));
}

int dfs(int u) {
	color[u] = true;
	for (auto v: adj[u]) {
		if (!color[v]) dfs(v);
		int temp = 0;
		if (hs[v] > hs[u]) temp = 1;
		value[u] = max(value[u], value[v] + temp);
	}
	return value[u];
}

ll farthest_delayed(int u) {
	if (color[u]) return fvalue[u];
	color[u] = true;
	ll cur_v = 1LL * (value[u] + 1) * k + hs[u];
	ll ans = cur_v;
	for (auto v: rev[u]) {
		ll child_v = 1LL * value[v] * k + hs[v];
		if (cur_v > child_v) {
			ans = max(ans, farthest_delayed(v));
		}
	}
	return fvalue[u] = ans;
}

auto solve() {
	// main logic comes here
	adj = vii(n, vi());
	rev = vii(n, vi());
	// rev.clear(); rev.resize(n);
	for (auto [u, v]: edges) {
		adj[v].push_back(u);
		rev[u].push_back(v);
		// trace(u _ v);
	}
	value = vi(n, 0);
	color = vector <bool> (n, false);
	color.clear(); color.resize(n, false);
	for (auto u: range(n)) {
		if (!color[u]) {
			dfs(u);
		}
	}
	color.assign(n, false);
	fvalue = vector<ll> (n, 0);
	ll right = -1;
	vector <tuple <int, ll, int> > total;
	for (auto u: range(n)) {
		if (value[u] == 0) {
			total.push_back({hs[u], farthest_delayed(u), u});
		}
		right = max(right, 1LL * value[u] * k + hs[u]);
	}
	sort(total.begin(), total.end());
	ll ans = ll(1e16);
	for (auto[le, shifted, u]: total) {
		ans = min(ans, right - le);
		right = max(right, shifted);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		read_input();
		auto ans = solve();
		cout << ans << endl;
	}
	return 0;
}

