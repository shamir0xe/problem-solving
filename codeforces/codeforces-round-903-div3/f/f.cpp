#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

/**
 * problem F (6/7)
 * codeforces, codeforces-round-903-div3
 * author: @shamir0xe
 * generated by contest-builder
 * https://github.com/shamir0xe/contest-builder
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
#define MAX_M 15
int n, k;
vi marked;
vvi adj;
vi max_dist;
vi answers;

// define functions here

int read_input() {
    cin >> n >> k;
    marked.assign(n, 0);
    for (int i: range(k)) {
        int temp; cin >> temp;
        marked[temp - 1] = 1;
    }
    adj.assign(n, vi());
    for (int i: range(n - 1)) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return 0;
}

void smax(int &a, int b) {
    if (a < b) a = b;
}

void smin(int &a, int b) {
    if (a > b) a = b;
}

int root(int u, int papa) {
    int &result = max_dist[u];
    if (marked[u]) smax(result, 0);
    for (int v: adj[u]) {
        if (v == papa) continue;
        int res = root(v, u);
        if (res == -1) continue;
        smax(result, res + 1);
    }
    return result;
}

void dfs(int u, int papa, int max_papa) {
    multiset<int> ms;
    // trace(u+1 _ papa _ max_papa _ max_dist[u]);
    int &result = answers[u];
    result = max_dist[u];
    if (max_papa == -1 && marked[u]) max_papa = 0;
    if (max_papa != -1) {
        ms.insert(max_papa + 1);
        smax(result, max_papa);
    }
    for (int v: adj[u]) {
        if (v == papa) continue;
        int temp = max_dist[v];
        if (temp != -1)
            ms.insert(temp + 2);
    }
    // if (u == 5) {
    // trace(u+1);
    // for (int t: ms) {
    //     trace(t);
    // }
    // }
    for (int v: adj[u]) {
        if (v == papa) continue;
        
        int temp = max_dist[v];
        if (temp != -1)
            ms.erase(ms.lower_bound(temp+2));
        int cur = -1;
        if (sz(ms) > 0)
            cur = *ms.rbegin();
        dfs(v, u, cur);
        if (temp != -1)
            ms.insert(temp+2);
    }
}

auto solve() {
    /**
     * main logic goes here
     **/
    max_dist.assign(n, -1);
    root(0, -1);
    answers.assign(n, 2e9);
    dfs(0, -1, -1);
    // trace(answers);
    int ans = *min_element(all(answers));
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

// 2
// 2
// 0
// 1
// 4
// 5

