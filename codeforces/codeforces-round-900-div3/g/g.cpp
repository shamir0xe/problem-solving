#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem G (7/7)
 * codeforces, codeforces-round-900-div3
 * author: @shamir0xe
 * verdict: [AC]
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
inline vi range(int idx, int n) {
    if (n <= idx)
        return vi();
    vi indices(n - idx);
    for (int i = idx; i < n; ++i)
        indices[i - idx] = i;
    return indices;
}

inline vi range(int n) { return range(0, n); }

// define variables here
#define MAX_BIT 31
#define MAX_BIT_N 18
int n;
vi arr;
int q;
vector<pii> queries;
vvi papa;
vvi closest;
vvi adj;
vi depth;
int cur_bit;

// define functions here

int read_input() {
    cin >> n;
    arr.resize(n);
    for (int i: range(n))
        cin >> arr[i];
    adj.resize(n);
    adj.assign(n, vi());
    for (int i: range(n - 1)) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> q;
    queries.clear();
    for (int i: range(q)) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        queries.push_back({u, v});
    }
    // trace("after input");
    return 0;
}

void smax(int &a, const int b) {
    if (a < b)
        a = b;
}

void dfs(int u, int father, int length) {
    papa[u][0] = father;
    depth[u] = length;
    for (int v: adj[u]) {
        if (v != father) {
            dfs(v, u, length + 1);
        }
    }
}

void root(int u, int father) {
    if (arr[father] >> cur_bit & 1) {
        closest[u][0] = father;
    } else {
        closest[u][0] = closest[father][0];
    }
    for (int v: adj[u]) {
        if (v != father) {
            root(v, u);
        }
    }
}

int find_common(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    int diff = depth[u] - depth[v];
    while (diff) {
        int index = log(diff & -diff) / log(2) + 1e-9;
        u = papa[u][index];
        diff ^= diff & -diff;
    }
    if (u == v)
        return u;
    for (int bit = MAX_BIT_N - 1; bit >= 0; bit--) {
        if (papa[u][bit] != papa[v][bit]) {
            u = papa[u][bit];
            v = papa[v][bit];
        }
    }
    return papa[u][0];
}

pii get_pairs(int u, int common) {
    int le = -1;
    if (arr[u] >> cur_bit & 1) {
        le = u;
    } else {
        le = closest[u][0];
    }
    if (le == -1 || depth[le] < depth[common])
        return {-1, -1};
    int ri = u;
    for (int i = MAX_BIT_N - 1; i >= 0; i--) {
        int temp = closest[ri][i];
        if (temp != -1 && depth[temp] >= depth[common]) {
            ri = temp;
        }
    }
    if (arr[common] >> cur_bit & 1)
        ri = common;
    return {le, ri};
}

auto solve() {
    /**
     * main logic goes here
     **/
    // papa[][], closest[][][], depth[]
    closest.resize(n);
    depth.resize(n);
    papa.resize(n, vi(MAX_BIT_N, -1));
    vi commons;
    vector<vector<tuple<int, int, int>>> stacks;
    stacks.resize(sz(queries));
    dfs(0, 0, 0);
    for (int bit: range(1, MAX_BIT_N)) {
        for (int u: range(n)) {
            papa[u][bit] = papa[papa[u][bit - 1]][bit - 1];
        }
    }
    for (const auto &[u, v]: queries) {
        commons.push_back(find_common(u, v));
    }
    for (int bbit: range(MAX_BIT)) {
        cur_bit = bbit;
        trace(cur_bit);
        closest.assign(n, vi(MAX_BIT_N, -1));
        root(0, 0);
        for (int bit: range(1, MAX_BIT_N)) {
            for (int u: range(n)) {
                if (closest[u][bit - 1] != -1)
                    closest[u][bit] = closest[closest[u][bit - 1]][bit - 1];
            }
        }
        for (int i: range(sz(queries))) {
            int &common = commons[i];
            int u = queries[i].X;
            int v = queries[i].Y;
            pii le = get_pairs(u, common);
            pii ri = get_pairs(v, common);
            if (le.X == -1 && ri.X == -1)
                continue;
            // trace(bit _ le _ ri);
            int length = depth[u] + depth[v] - 2 * depth[common];
            int lele = -1;
            int riri = -1;
            if (le.X != -1) {
                lele = depth[u] - depth[le.X];
            }
            if (ri.X != -1) {
                riri = length - (depth[v] - depth[ri.X]);
            }
            if (lele == -1) {
                lele = depth[u] + depth[ri.Y] - 2 * depth[common];
            }
            if (riri == -1) {
                riri = depth[u] - depth[le.Y];
            }
            stacks[i].push_back({lele, 1, cur_bit});
            stacks[i].push_back({riri, 2, cur_bit});
        }
    }
    for (int i: range(sz(queries))) {
        auto &stack = stacks[i];
        sort(all(stack));
        int res = 0;
        vi rev{0};
        int cr = 0;
        for (int i = sz(stack) - 1; i >= 0; i--) {
            int bit = get<2>(stack[i]);
            cr |= 1 << bit;
            rev.push_back(__builtin_popcount(cr));
        }
        rev.pop_back();
        reverse(all(rev));
        int cl = 0;
        for (int i: range(sz(stack))) {
            int bit = get<2>(stack[i]);
            cl |= 1 << bit;
            smax(res, __builtin_popcount(cl) + rev[i]);
        }
        cout << res << ' ';
    }
    cout << endl;
    return 0;
}

int second_main() {
    read_input();
    auto ans = solve();
    // for (int t: ans)
    //     cout << t << ' ';
    // cout << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = true;
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
