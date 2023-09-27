#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/5)
 * codeforces, codeforces-round-899-div2
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
int n;
vvi adj;
vector<ll> arr;
vector<ll> cnts;
int cur_bit;
vi child_cnt;

// define functions here
void root(int u, int papa) {
    for (int v: adj[u])
        if (v != papa) {
            root(v, u);
            child_cnt[u] += child_cnt[v];
        }
    child_cnt[u]++;
}

ll global_ans(int u, int papa) {
    ll &ans = cnts[u] = 0;
    for (int v: adj[u])
        if (v != papa) {
            ll temp = global_ans(v, u);
            // trace("global_ans" _ v + 1 _ temp);
            ans += temp;
            if ((arr[u] >> cur_bit & 1) != (arr[v] >> cur_bit & 1)) {
                ans += child_cnt[v];
            }
        }
    return ans;
}

int fn(int u, int papa) {
    ll &ans = cnts[u];
    if (papa != -1) {
        if ((arr[u] >> cur_bit & 1) == (arr[papa] >> cur_bit & 1)) {
            ans = cnts[papa];
        } else {
            ans = cnts[papa] + n - 2 * child_cnt[u];
        }
    }
    for (int v: adj[u])
        if (v != papa) {
            fn(v, u);
        }
    return ans;
}

int read_input() {
    cin >> n;
    arr.resize(n);
    for (int i: range(n))
        cin >> arr[i];
    adj.clear();
    adj.assign(n, vi());
    for (int i: range(n - 1)) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    vector<ll> ans(n, 0);
    int max_bit = 20;
    for (int bit = 0; bit < max_bit; bit++) {
        cur_bit = bit;
        child_cnt.assign(n, 0);
        root(0, -1);
        cnts.assign(n, 0);
        global_ans(0, -1);
        fn(0, -1);
        for (int i: range(n)) {
            ans[i] += (1LL << bit) * cnts[i];
        }
    }
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    for (ll t: ans)
        cout << t << ' ';
    cout << endl;
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
