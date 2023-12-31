#include <bits/stdc++.h>
using namespace std;

/**
 * problem E (5/7)
 * codeforces, educational-codeforces-round-156-rated-for-div2
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
#define EPS 1e-12
int n, m;
vi a, b;

// define functions here

int read_input() {
    cin >> n >> m;
    a.resize(n);
    for (int i: range(n))
        cin >> a[i];
    b.resize(m);
    for (int j: range(m))
        cin >> b[j];
    return 0;
}

tuple<bool, vvi> solve() {
    /**
     * main logic goes here
     **/
    vector<pii> aa;
    aa.resize(n);
    for (int i: range(n)) {
        aa[i] = {a[i], i};
    }
    sort(all(aa));
    reverse(all(aa));
    vvi dist(m, vi(n));
    for (int j: range(m)) {
        for (int i: range(n)) {
            int &s = dist[j][i];
            if (i > 0)
                s = max(dist[j][i - 1], i);
            else
                s = 0;
            while (s < n && 1ll * (s - i + 1) * aa[s].X < b[j])
                s++;
        }
        // trace(j _ dist[j]);
    }
    vi dp(1 << m, 1e9);
    vi par(1 << m, -1);
    dp[0] = -1;
    for (int j: range(m)) {
        dp[1 << j] = dist[j][0];
        par[1 << j] = 0;
    }
    for (int mask: range(1, 1 << m)) {
        for (int j: range(m)) {
            if (mask >> j & 1)
                continue;
            if (dp[mask] + 1 >= n)
                continue;
            // trace(j _ mask _ dist[j][dp[mask]]);
            int next_mask = mask | 1 << j;
            int t = dist[j][dp[mask] + 1];
            if (t >= n)
                continue;
            if (dp[next_mask] > t) {
                dp[next_mask] = t;
                par[next_mask] = mask;
            }
        }
    }
    int mask = (1 << m) - 1;
    vvi tasks(m);
    // trace(dp[mask]);
    if (dp[mask] >= n)
        return {false, vvi()};
    while (mask != 0) {
        int par_mask = par[mask];
        int idx = log(par_mask ^ mask) / log(2) + EPS;
        // trace(idx);
        for (int i: range(dp[par_mask] + 1, dp[mask] + 1)) {
            tasks[idx].push_back(aa[i].Y);
        }
        mask = par_mask;
    }
    return {true, tasks};
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << (get<0>(ans) ? "YES" : "NO") << endl;
    if (get<0>(ans)) {
        for (vi &t: get<1>(ans)) {
            cout << sz(t) << ' ';
            for (int &tt: t)
                cout << tt + 1 << ' ';
            cout << endl;
        }
        cout << endl;
    }
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
