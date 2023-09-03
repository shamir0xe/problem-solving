#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/4)
 * leetcode, Weekly-Contest-361
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
 **/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

/**
 * printing tuples
 **/
template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup){};

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup) {
    if (n != 0)
        os << " ";
    os << get<n>(tup);
    __tuple_printer<n + 1>(os, tup);
};

template <typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "(";
    __tuple_printer<0>(os, tup);
    os << ")";
    return os;
}

/**
 * printing pairs
 **/
template <typename T, typename K>
ostream &operator<<(std::ostream &os, const std::pair<T, K> &p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}

/**
 * printing vectors
 **/
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    bool first = true;
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if (first)
            first = false;
        else
            os << " ";
        os << (*ii);
    }
    os << "]";
    return os;
}

/**
 * range functions
 **/
inline vi range(const int idx, const int n) {
    if (n <= idx)
        return vi();
    vi indices(n - idx);
    for (int i = idx; i < n; ++i)
        indices[i - idx] = i;
    return indices;
}

inline vi range(const int n) { return range(0, n); }

// define variables here
#define MAX_M 22
#define MAX_W 26
int n;
vvi edges, queries;
vvi par_lca;
vi depths;
vector<vector<pii>> adj;
vvi weights;

// define functions here
int dfs(int u, int papa, int w, int depth) {
    par_lca[u].resize(MAX_M);
    par_lca[u][0] = papa;
    depths[u] = depth;
    if (u == papa)
        weights[u] = vi(MAX_W, 0);
    weights[u] = weights[papa];
    if (w > 0)
        weights[u][w - 1] += 1;
    for (auto const &[v, w] : adj[u]) {
        if (v != papa) {
            dfs(v, u, w, depth + 1);
        }
    }
    return 0;
}

inline int merge_weights(vi &a, vi &b) {
    for (int &k : range(MAX_W)) {
        a[k] += b[k];
    }
    return 0;
}

int calc_lca() {
    int n = sz(adj);
    for (int &j : range(1, MAX_M)) {
        for (int &i : range(n)) {
            par_lca[i][j] = par_lca[par_lca[i][j - 1]][j - 1];
        }
    }
    return 0;
}

vi lca(int u, int v) {
    vi ans = vi(MAX_W, 0);
    if (depths[u] < depths[v])
        swap(u, v);
    merge_weights(ans, weights[u]);
    merge_weights(ans, weights[v]);
    int diff = depths[u] - depths[v];
    while (diff) {
        int j = round(log(diff & -diff) / log(2)) + 1e-9;
        u = par_lca[u][j];
        diff ^= 1 << j;
    }
    int common_ancestor = u;
    if (u != v) {
        for (int j = MAX_M - 1; j >= 0; j--) {
            if (par_lca[u][j] == par_lca[v][j])
                continue;
            u = par_lca[u][j];
            v = par_lca[v][j];
        }
        common_ancestor = par_lca[u][0];
    }
    for (int &k : range(MAX_W)) {
        ans[k] -= 2 * weights[common_ancestor][k];
    }
    return ans;
}

class Solution {
  public:
    vector<int> minOperationsQueries(int n, vector<vector<int>> &edges,
                                     vector<vector<int>> &queries) {
        adj.clear();
        weights.clear();
        adj.resize(n);
        for (auto const &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        par_lca.resize(n);
        weights.resize(n);
        depths.resize(n);
        dfs(0, 0, 0, 0);
        calc_lca();
        vi ans;
        for (auto const &query : queries) {
            int u = query[0];
            int v = query[1];
            vi merged_weights = lca(u, v);
            ans.push_back(accumulate(all(merged_weights), 0) -
                          *max_element(all(merged_weights)));
        }
        return ans;
    }
};

int read_input() {
    int t;
    cin >> n >> t;
    for (int &i : range(n - 1)) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(vi{u, v, w});
    }
    for (int &i : range(t)) {
        int u, v;
        cin >> u >> v;
        queries.push_back(vi{u, v});
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.minOperationsQueries(n, edges, queries);
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << ans << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = false;
    if (test_case) {
        int t;
        cin >> t;
        while (t--) {
            second_main();
        }
    } else {
        second_main();
    }
    return 0;
}
